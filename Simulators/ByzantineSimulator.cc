/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"

namespace simulators {

ByzantineSimulator::ByzantineSimulator() : SimulatorBase() {
	_byzantine = new ByzantineProtocol(0.5, 0.5);
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
		//_fault->tolerance = ToleranceBase::GetBase();
		_byzantine->tolerance = new ToleranceBase();
		break;
	default:
		_byzantine->tolerance = new ToleranceBase();
		break;
	}
}

void ByzantineSimulator::InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw)
{
	SetTolerance(toleranceType);
	_byzantine->Initialize(_network, byzantineProb, nothingProb);
//	if (draw)
//		_networkGraphics.DrawNetwork(_network, false, false, true);
}

bool ByzantineSimulator::RunSimulationStep(bool draw)
{
	bool stop = _byzantine->RunStepCheckFinish(_network, &Network::noNewMessageInNetwork);
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
	_byzantine->report->byzantineProbability = _byzantine->byzantineProb;
	_byzantine->report->AddByzantineValue(byzantines);
	_byzantine->report->AddSacrificeValue(inactives);
	_byzantine->report->AddDetectorValue(detectors);
	_byzantine->report->AddNormalValue(_network->nodes->size() - byzantines - inactives - detectors);
	_byzantine->report->AddLargestConnectedAreaValue(
			_deploying->FindMaximumConnectedArea(_network, &Node::isNodeState, Sane));
}

ByzantineReport* ByzantineSimulator::FinishReport()
{
	_byzantine->report->Clear();
	AddOneStepReport();
	_byzantine->report->Summarize(0.05);
	return _byzantine->report;
}

bool ByzantineSimulator::StopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::RunSimulationByInterval(int times)
{
	_byzantine->report->Clear();
	_byzantine->report->nothingProbability = _byzantine->nothingProb;
	int prediction = 500;
	int count = 0;
	while (count < times)
	{
		while (count < prediction)
		{
			_byzantine->Refresh(_network);
			_byzantine->RunFault(_network);
			AddOneStepReport();
			count++;
		}
		_byzantine->report->Summarize(0.05);
		if (StopPrediction(_byzantine->report))
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
	_byzantine->Initialize(_network, byzantineProb, nothingProb);
	RunSimulationByInterval(times);
	output(ByzantineReport());
}

} /* namespace deployment */
