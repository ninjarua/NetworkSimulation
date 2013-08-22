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

//	SimulatorManager* manager = new SimulatorManager();
//	manager->readOneStepResults(Small_world, C01, "/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/C01_new_0",
//				"/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/C01_new_0.out", 0.25, 0.01);
//	manager->readOneStepResults(Small_world, K01, "/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0",
//				"/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0.out", 0.25, 0.01);

//	manager->ReadOneStepResults(TorusGrid, KxHop, "/Users/thanhnd/Workspace/Results/TorusGrid/2500/K01Hop_0",
//				"/Users/thanhnd/Workspace/Results/TorusGrid/2500/K01Hop_0.out", 0, 0.01);

//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0.out", 0, 0.01);

	SimulatorBase* sim = new SimulatorBase();
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/1000", 8, 4000, 4000, 275, 1);
	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/4000", 8, 4000, 4000, 135.5, 1);
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/10000", 8, 4000, 4000, 85.25, 1);

	SimulatorManager* manager = new SimulatorManager();
	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_8/4000",
				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/degree/14_8/4000", 100, false);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_2/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_2/degree/4000", 100, false);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_2/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_2/degree/10000", 100, false);
}
