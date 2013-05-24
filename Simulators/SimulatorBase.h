/*
 * PropagationSimulator.h
 *
 *  Created on: May 23, 2013
 *      Author: thanh
 */

#ifndef SIMULATORBASE_H_
#define SIMULATORBASE_H_

#include "stdafx.h"
#include <string>

#include "Network.h"
#include "Topology.h"
#include "Deploying.h"
#include "ByzantineProtocol.h"

using namespace domain;
using namespace deployment;
using namespace protocols;

namespace simulators {

class SimulatorBase {
public:
	SimulatorBase();
	virtual ~SimulatorBase();
protected:
	Deploying* _deploying;
	//NetworkGraphics _networkGraphics;
	Network* _network;
	Topology* _topology;
	bool _hasTopology;
	int _currentTimeslot;
	ByzantineProtocol _fault;
	virtual void SetDeployment(DeployingType type);

public:
	int timeslot;
	void GetParameters(DeployingType deployingType, int numberOfNodes, int transRange, float xTerr, float yTerr, float d0, bool checkConflict);
	//void CreateGraphic(Graphics graphic, float width, float height, float margin, Color backColor);
	string DeployNetwork(bool drawNetwork);

//FaultProtocol _fault = FaultProtocol.GetInstance(0.5, 0.5);

//	TypeOfTolerance ToleranceType;
//
//	void SetTolerance(TypeOfTolerance toleranceType);
//
//	void InitializeSimulator(double byzantineProb, double nothingProb, TypeOfTolerance toleranceType, bool draw = false)
//        {
//            SetTolerance(toleranceType);
//            _fault.Initialize(_network, byzantineProb, nothingProb);
//            if (draw)
//                _networkGraphics.DrawNetwork(_network, false, false, true);
//        }

//        public bool RunSimulationStep(bool draw = false)
//        {
//            bool stop = _fault.RunStepCheckFinish(_network, () => _network.NewMessages.Count == 0);
//            _networkGraphics.DrawNetwork(_network, false, false, true);
//            return stop;
//        }
//
//        public void DrawNetwork()
//        {
//            _networkGraphics.DrawNetwork(_network, false, false, true);
//        }
//
//        private void AddOneStepReport()
//        {
//            int byzantines = _network.GetNodes().FindAll(n => n.State == NodeState.Infected).Count;
//            int inactives = _network.GetNodes().FindAll(n => n.State == NodeState.Inactive).Count;
//            int detectors = _network.GetNodes().FindAll(n => n.State == NodeState.Detector).Count;
//            ByzantineReport.Default.ByzantineProbability = _fault.ByzantineProb;
//            ByzantineReport.Default.AddByzantineValue(byzantines);
//            ByzantineReport.Default.AddSacrificeValue(inactives);
//            ByzantineReport.Default.AddDetectorValue(detectors);
//            ByzantineReport.Default.AddNormalValue(_network.GetNodes().Count - byzantines - inactives - detectors);
//            ByzantineReport.Default.AddLargestConnectedAreaValue(_protocolSet.DeployingProtocol
//                                    .FindMaximumConnectedArea(_network, n => n.State == NodeState.Sane));
//        }
//
//        public ByzantineReport FinishReport()
//        {
//            ByzantineReport.Default.Clear();
//            AddOneStepReport();
//            ByzantineReport.Default.Summarize(0.1);
//            return ByzantineReport.Default;
//        }
//
//        public bool StopPrediction(ByzantineReport report)
//        {
//            bool averageCondition = (report.CIOfByzantines < .8)
//                && (report.CIOfNormals < 0.01 || (report.CIOfNormals < .8 && report.CIOfNormals <= report.AverageOfNormals));
//            //if ((report.CIOfByzantines < 1 && report.CIOfNormals < 1 && report.CIOfLargestConnectedAreas < 1)
//            //    || averageCondition)
//            //    return true;
//            //return false;
//            return averageCondition;
//        }
//
//        public void RunSimulationByInterval(int times)
//        {
//            ByzantineReport.Default.Clear();
//            ByzantineReport.Default.NothingProbability = _fault.NothingProb;
//            int prediction = 500;
//            int count = 0;
//            while (count < times)
//            {
//                while (count < prediction)
//                {
//                    _fault.Refresh(_network);
//                    _fault.RunFault(_network);
//                    AddOneStepReport();
//                    count++;
//                }
//                ByzantineReport.Default.Summarize(0.1);
//                if (StopPrediction(ByzantineReport.Default))
//                    times = prediction;
//                else
//                    prediction += 100;
//            }
//        }
//
//        public void RunSimulation(int times, double intervalByz, double intervalNothing,
//                                TypeOfTolerance toleranceType, Action<ByzantineReport> output,
//                                double startingNothing = 0, double startingByzantine = 0)
//        {
//            SetTolerance(toleranceType);
//            int nothingSteps = Convert.ToInt32(1 / intervalNothing); // ex: 1000
//            int byzSteps = Convert.ToInt32(1 / intervalByz); // ex: 10
//            int nothingStart = Convert.ToInt32(startingNothing / intervalNothing);
//            int byzantineStart = Convert.ToInt32(startingByzantine / intervalNothing);
//            double ratio = (double)nothingSteps / byzSteps;
//
//            for (int j = byzantineStart; j < Convert.ToInt32((nothingSteps - nothingStart)/ratio); j++)
//                RunOneStep(output, j * intervalByz, nothingStart * intervalNothing, times);
//            RunOneStep(output, (nothingSteps - nothingStart) * intervalNothing, nothingStart * intervalNothing, 2);
//
//            for (int i = nothingStart + 1; i < nothingSteps; i++)
//            {
//                for (int j = 0; j < Convert.ToInt32((nothingSteps - i) / ratio); j++)
//                    RunOneStep(output, j * intervalByz, i * intervalNothing, times);
//                RunOneStep(output, (nothingSteps - i) * intervalNothing, i * intervalNothing, 2);
//            }
//            long length = GC.GetTotalMemory(true);
//            GC.RemoveMemoryPressure(length);
//        }
//
//        private void RunOneStep(Action<ByzantineReport> output,
//                                double byzantineProb, double nothingProb, int times)
//        {
//            _fault.Initialize(_network, byzantineProb, nothingProb);
//            RunSimulationByInterval(times);
//            //reports.Add(report);
//            output(ByzantineReport.Default);
//        }
};

} /* namespace deployment */
#endif /* SIMULATORBASE_H_ */
