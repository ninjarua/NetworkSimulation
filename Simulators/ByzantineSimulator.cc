/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"

namespace simulators {

ByzantineSimulator::ByzantineSimulator() : SimulatorBase() {
	_fault = ByzantineProtocol::GetInstance(0.5, 0.5);
}

ByzantineSimulator::~ByzantineSimulator() {

}

NetworkInfo* ByzantineSimulator::GetNetworkInfo()
{
	return _network->info;
}

void ByzantineSimulator::SetTolerance(TypeOfTolerance toleranceType)
{
	switch(toleranceType)
	{
	case K01:
		_fault->tolerance = ToleranceBase::GetBase();
		break;
	}
}

void ByzantineSimulator::InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw)
{
	SetTolerance(toleranceType);
	_fault->Initialize(_network, byzantineProb, nothingProb);
//	if (draw)
//		_networkGraphics.DrawNetwork(_network, false, false, true);
}

bool ByzantineSimulator::RunSimulationStep(bool draw)
{
	bool stop = _fault->RunStepCheckFinish(_network, &Network::noNewMessageInNetwork);
	//_networkGraphics.DrawNetwork(_network, false, false, true);
	return stop;
}

void ByzantineSimulator::DrawNetwork()
{

}

void ByzantineSimulator::AddOneStepReport()
{
	long byzantines = Tools::CountAll(*_network->nodes, &Node::isNodeState, Infected);
	long inactives = Tools::CountAll(*_network->nodes, &Node::isNodeState, Inactive);
	long detectors = Tools::CountAll(*_network->nodes, &Node::isNodeState, Detector);
	ByzantineReport::Default()->byzantineProbability = _fault->byzantineProb;
	ByzantineReport::Default()->AddByzantineValue(byzantines);
	ByzantineReport::Default()->AddSacrificeValue(inactives);
	ByzantineReport::Default()->AddDetectorValue(detectors);
	ByzantineReport::Default()->AddNormalValue(_network->nodes->size() - byzantines - inactives - detectors);
	ByzantineReport::Default()->AddLargestConnectedAreaValue(
			_deploying->FindMaximumConnectedArea(_network, &Node::isNodeState, Sane));
}

ByzantineReport* ByzantineSimulator::FinishReport()
{
	ByzantineReport::Default()->Clear();
	AddOneStepReport();
	ByzantineReport::Default()->Summarize(0.05);
	return ByzantineReport::Default();
}

bool ByzantineSimulator::StopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::RunSimulationByInterval(int times)
{
	ByzantineReport::Default()->Clear();
	ByzantineReport::Default()->nothingProbability = _fault->nothingProb;
	int prediction = 500;
	int count = 0;
	while (count < times)
	{
		while (count < prediction)
		{
			_fault->Refresh(_network);
			_fault->RunFault(_network);
			AddOneStepReport();
			count++;
		}
		ByzantineReport::Default()->Summarize(0.05);
		if (StopPrediction(ByzantineReport::Default()))
			times = prediction;	// reduce the running time and quit
		else
			prediction += 100;
	}
}

void ByzantineSimulator::RunSimulation(int times, double intervalByz, double intervalNothing, TypeOfTolerance toleranceType,
		void (*output)(ByzantineReport), double startingNothing, double startingByzantine, double endingNothing, double endingByzantine)
{
	SetTolerance(toleranceType);
	int nothingSteps = (int)(1 / intervalNothing); // ex: 1000
	int byzSteps = (int)(1 / intervalByz); // ex: 10
	int nothingStart = (int)(startingNothing / intervalNothing);
	int nothingEnd = (int)(endingNothing / intervalNothing);
	int byzantineStart = (int)(startingByzantine / intervalNothing);
	int byzantineEnd = (int)(endingByzantine / intervalNothing);
	double ratio = (double)nothingSteps / byzSteps;

	for (int j = byzantineStart; j < (int)((nothingSteps - nothingStart)/ratio); j++)
		RunOneStep(output, j * intervalByz, nothingStart * intervalNothing, times);
	RunOneStep(output, (nothingSteps - nothingStart) * intervalNothing, nothingStart * intervalNothing, 2);

	for (int i = nothingStart + 1; i < nothingSteps; i++)
	{
		for (int j = 0; j < (int)((nothingSteps - i) / ratio); j++)
			RunOneStep(output, j * intervalByz, i * intervalNothing, times);
		RunOneStep(output, (nothingSteps - i) * intervalNothing, i * intervalNothing, 2);
	}

	if (endingNothing == 1)
		return;
	for (int j = 0; j < byzantineEnd && j < (int)((nothingSteps - nothingEnd) / ratio); j++)
		RunOneStep(output, j * intervalByz, nothingEnd * intervalNothing, times);
	RunOneStep(output, (nothingSteps - nothingEnd) * intervalByz, nothingEnd * intervalNothing, times);
}

void ByzantineSimulator::RunOneStep(void (*output)(ByzantineReport), double byzantineProb, double nothingProb, int times)
{
	_fault->Initialize(_network, byzantineProb, nothingProb);
	RunSimulationByInterval(times);
	output(ByzantineReport::Default());
}

} /* namespace deployment */
