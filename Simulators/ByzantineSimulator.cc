/*
 * PropagationSimulator.cpp
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#include "ByzantineSimulator.h"

namespace simulators {

ByzantineSimulator::ByzantineSimulator() : SimulatorBase() {
	_byzantine = ByzantineProtocol(0.5, 0.5);
}

ByzantineSimulator::~ByzantineSimulator() {

}

void ByzantineSimulator::SetTolerance(TypeOfTolerance toleranceType)
{
	switch(toleranceType)
	{
	case K01:
		//_fault->tolerance = ToleranceBase::GetBase();
		_byzantine.tolerance = new ToleranceBase();
		break;
	default:
		_byzantine.tolerance = new ToleranceBase();
		break;
	}
}

void ByzantineSimulator::InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw)
{
	SetTolerance(toleranceType);
	_byzantine.Initialize(_network, byzantineProb, nothingProb);
	_byzantine.Refresh(_network);
//	if (draw)
//		_networkGraphics.DrawNetwork(_network, false, false, true);
}

bool ByzantineSimulator::RunSimulationStep(bool draw)
{
	bool stop = _byzantine.RunStepCheckFinish(_network, &Network::noNewMessageInNetwork);
	//_networkGraphics.DrawNetwork(_network, false, false, true);
	return stop;
}

void ByzantineSimulator::DrawNetwork()
{

}

void ByzantineSimulator::AddOneStepReport()
{
	_byzantine.report->byzantineProb = _byzantine.byzantineProb;
	_byzantine.report->AddByzantineValue(_byzantine.statisticInfo->infections);
	_byzantine.report->AddSacrificeValue(_byzantine.statisticInfo->inactives);
	_byzantine.report->AddDetectorValue(_byzantine.statisticInfo->detectors);
	_byzantine.report->AddNormalValue(_byzantine.statisticInfo->sanes);
	_byzantine.report->AddLargestConnectedAreaValue(_byzantine.statisticInfo->lca);
}

ByzantineReport* ByzantineSimulator::FinishReport()
{
	_byzantine.report->Clear();
	AddOneStepReport();
	_byzantine.report->Summarize(0.05);
	return _byzantine.report;
}

bool ByzantineSimulator::StopPrediction(ByzantineReport* report)
{
    bool averageCondition = (report->ciOfByzantines < .8)
        && (report->ciOfNormals < 0.01 || (report->ciOfNormals < .8 && report->ciOfNormals <= report->averageOfNormals));
    return averageCondition;
}

void ByzantineSimulator::RunSimulationByInterval(int times)
{
	_byzantine.report->Clear();
	_byzantine.report->nothingProb = _byzantine.nothingProb;
	if (_byzantine.nothingProb + _byzantine.byzantineProb > 0.991)
		times = 2;
	int prediction = (times < 500) ? times : 500;
	int count = 0;
	while (count < times)
	{
		while (count < prediction)
		{
			_byzantine.Refresh(_network);
			_byzantine.RunFault(_network);
			AddOneStepReport();
			count++;
		}
		_byzantine.report->Summarize(0.05);
		if (StopPrediction(_byzantine.report))
			times = prediction;	// reduce the running time and quit
		else
			prediction += 100;
	}
}

string ByzantineSimulator::GetResultFilename()
{
	string filename = _deploying->GetDeployingName();
	filename += "_";
	filename += _byzantine.tolerance->GetToleranceName();
	filename += ".out";
	return filename;
}

void ByzantineSimulator::RunSimulation(int times, double intervalByz, double intervalNothing, TypeOfTolerance toleranceType,
		void (*output)(ByzantineReport&, string), double startingNothing, double startingByzantine, double endingNothing, double endingByzantine)
{
	SetTolerance(toleranceType);
	int nothingSteps = (int)(100 / (int)(intervalNothing * 100)); // ex: 1000
	int byzSteps = (int)(100 / (int)(intervalByz * 100)); // ex: 10
	int nothingStart = (int)(startingNothing / intervalNothing);
	int nothingEnd = (int)(endingNothing / intervalNothing);
	int byzantineStart = (int)(startingByzantine / intervalNothing);
	int byzantineEnd = (int)(endingByzantine / intervalNothing);
	double ratio = (double)nothingSteps / byzSteps;

	if (nothingStart == nothingEnd)
	{
		for (int j = byzantineStart; j <= byzantineEnd; j++)
			RunOneStep(output, j * intervalByz, nothingStart * intervalNothing, times);
	}
	else
	{
		for (int j = byzantineStart; j <= (int)((nothingSteps - nothingStart)/ratio); j++)
			RunOneStep(output, j * intervalByz, nothingStart * intervalNothing, times);
		for (int i = nothingStart + 1; i < nothingEnd && i < nothingSteps; i++)
		{
			for (int j = 0; j <= (int)((nothingSteps - i) / ratio); j++)
				RunOneStep(output, j * intervalByz, i * intervalNothing, times);
		}
		for (int j = 0; j <= byzantineEnd && j <= (int)((nothingSteps - nothingEnd) / ratio); j++)
			RunOneStep(output, j * intervalByz, nothingEnd * intervalNothing, times);
	}
}

void ByzantineSimulator::RunOneStep(void (*output)(ByzantineReport&, string), double byzantineProb, double nothingProb, int times)
{
	_byzantine.Initialize(_network, byzantineProb, nothingProb);
	RunSimulationByInterval(times);
	output(*_byzantine.report, GetResultFilename());
}

} /* namespace deployment */
