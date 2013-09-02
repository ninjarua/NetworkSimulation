/*
 * main.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "stdafx.h"
#include "SimulatorManager.h"
#include "nsException.h"
#include "Logger.h"
#include <iostream>
#include <cstring>

using namespace std;
using namespace simulators;

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	srand(time(NULL)); // Set random seed for random procedure

	SimulatorManager* manager = new SimulatorManager();
	manager->runOneStepSimulation(Small_world, CBridges, 10000, 0, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_5/1000",
			"/Users/thanhnd/Workspace/Results/Smallworld/10_5/1000/CBridges_0", 1, 100);

//	manager->readOneStepResults(Small_world, C01, "/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/C01_new_0",
//				"/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/C01_new_0.out", 0.25, 0.01);
//	manager->readOneStepResults(Small_world, K01, "/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0",
//				"/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0.out", 0.25, 0.01);

//	SimulatorBase* sim = new SimulatorBase();
//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/1000", 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateFixedRangeNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/4000", 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateFixedRangeNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/10000", 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_1/1000", 10, 1, 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_1/4000", 10, 1, 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_1/10000", 10, 1, 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_2/1000", 10, 2, 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_2/4000", 10, 2, 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_2/10000", 10, 2, 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_3/1000", 10, 3, 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_3/4000", 10, 3, 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_3/10000", 10, 3, 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_4/1000", 10, 4, 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_4/4000", 10, 4, 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_4/10000", 10, 4, 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_10/1000", 10, 10, 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_10/4000", 10, 10, 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_10/10000", 10, 10, 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56

//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_0/10000", 14, 0, 48, 46, 1, 0.01); //15x14, 30x29
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/4000", 14, 8, 4000, 4000, 135.5, 0.01);
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/10000", 14, 8, 4000, 4000, 85.25, 0.01);

//	sim->generateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/14/1000", 7, 1000, 7);
//	sim->generateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/14/1000", 7, 2000, 7);
//	sim->generateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/14/1000", 7, 3000, 7);

//	SimulatorManager* manager = new SimulatorManager();
//	manager->convert2HopInformation(FixedRange, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_3/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_3/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_4/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_4/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_5/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_5/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_10/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_10/4000", 100, true);
}

