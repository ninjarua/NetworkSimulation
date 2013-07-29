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

static void show_missing_generate_arguments(int numbers)
{
	std::cerr << "Please input necessary " << numbers << " arguments:\n"
			  << "\t\t-3rd: deployment type\n"
			  << "\t\t-4th: number of Nodes in graph\n"
			  << "\t\t-5th: width of deploying area\n"
			  << "\t\t-6th: height of deploying area\n"
			  << "\t\t-7th: transmission range\n"
			  << "\t\t-8th: number of generated graph\n"
			  << "\t\t-9th: output folder\n"
			  << std::endl;
}

static void show_missing_simulate_arguments(int numbers)
{
	std::cerr << "Please input necessary " << numbers << " arguments:\n"
			  << "\t\t-3rd: deployment type\n"
			  << "\t\t-4th: tolerance strategy\n"
			  << "\t\t-5th: total running times\n"
			  << "\t\t-6th: input folder of graphs\n"
			  << "\t\t-7th: output folder of results\n"
			  << "\t\t-8th: number of CPUs\n"
			  << "\t\t-9th: number of samples for each strategy\n"
			  << std::endl;
}

DeployingType GetDeployingType(char* type)
{
	if (strcmp(type, "FixedRange") == 0)
		return FixedRange;
	else if (strcmp(type, "Grid") == 0)
		return Grid;
	else if (strcmp(type, "Torus") == 0)
		return TorusGrid;
	else if (strcmp(type, "ER") == 0)
		return ER_Random;
	else if (strcmp(type, "ScaleFree") == 0)
		return ScaleFree;
	return TorusGrid;
}

TypeOfTolerance GetToleranceType(char* type)
{
	if (strcmp(type, "K1") == 0)
		return K01;
	else if (strcmp(type, "K3") == 0)
		return K03;
	else if (strcmp(type, "K4") == 0)
		return K04;
	else if (strcmp(type, "K5") == 0)
		return K05;
	else if (strcmp(type, "K7") == 0)
		return K07;
	else if (strcmp(type, "K11") == 0)
		return KxHop;
	return K01;
}

void showArgumentDebugGenerateGraph(char* argv[])
{
	cout << "Deploying: " << GetDeployingType(argv[3]) << "\n";
	cout << "int numberOfNode: " << atoi(argv[4]) << "\n";
	cout << "float xTerr: " << atof(argv[5]) << "\n";
	cout << "float yTerr: " << atof(argv[6]) << "\n";
	cout << "float range: " << atof(argv[7]) << "\n";
	cout << "int times: " << atoi(argv[8]) << "\n";
	cout << "string folder: " << argv[9] << "\n";
}

//void generateGraph(int argc, char* argv[])
//{
//	if (argc < 10)
//	{
//		show_missing_generate_arguments(9);
//	}
//	else
//	{
//		ByzantineSimulator* sim = new ByzantineSimulator();
//		sim->generateNetwork(GetDeployingType(argv[3]), atoi(argv[4]), atoi(argv[8]), argv[9],
//				atof(argv[5]), atof(argv[6]), atof(argv[7]), 1);
//		delete sim;
////		showArgumentDebugGenerateGraph(argv);
//	}
//}

void showArgumentDebugSimulation(char* argv[])
{
	cout << "Deploying: " << GetDeployingType(argv[3]) << "\n";
	cout << "Tolerance Type: " << GetToleranceType(argv[4]) << "\n";
	cout << "Total times: " << atoi(argv[5]) << "\n";
	cout << "input folder: " << argv[6] << "\n";
	cout << "output folder: " << argv[7] << "\n";
	cout << "number of CPUs: " << atoi(argv[8]) << "\n";
	cout << "samples size: " << atoi(argv[9]) << "\n";
}

void runSimulation(int argc, char* argv[])
{
	if (argc < 10)
	{
		show_missing_simulate_arguments(9);
	}
	else
	{
		try
		{
			SimulatorManager* manager = new SimulatorManager();
						manager->runSimulation(GetDeployingType(argv[3]),
								GetToleranceType(argv[4]), 1, atoi(argv[5]),
								argv[6], argv[7], atoi(argv[8]), atoi(argv[9]));
		}
		catch (std::exception& ex)
		{
			cout << "Got " << ex.what() << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL)); // Set random seed for random procedure
//	SimulatorManager* manager = new SimulatorManager();
//	manager->runOneStepSimulation(ER_Random, K01, 1, 10000, 0.5,
//				"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/10/1000",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/50/K01_0", 2, 100);
//	manager->runOneStepSimulation(ER_Random, K01, 1, 10000, 0.5,
//				"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/10/10000",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/10000/50/K01_0", 2, 100);

//	SimulatorManager* manager = new SimulatorManager();
//	manager->readOneStepResults(TorusGrid, K01, "/Users/thanhnd/Workspace/Results/TorusGrid/2500/K0Hop_0",
//				"/Users/thanhnd/Workspace/Results/TorusGrid/2500/K0Hop_0.out", 0, 0.01);
//	manager->ReadOneStepResults(TorusGrid, KxHop, "/Users/thanhnd/Workspace/Results/TorusGrid/2500/K01Hop_0",
//				"/Users/thanhnd/Workspace/Results/TorusGrid/2500/K01Hop_0.out", 0, 0.01);

//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0.out", 0, 0.01);

	ByzantineSimulator* sim = new ByzantineSimulator();
//	sim->Convert2HopInformation(ER_Random, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/14/10000",
//			"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/14/advanced/10000", 101);
//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/FixedRange/10/1000", 4000, 4000, 276, 1);
	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/14_5/1000", 5, 4000, 4000, 276, 1);
}
