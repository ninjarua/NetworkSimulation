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

//static void show_usage(string name)
//{
//	std::cerr << "Usage: " << name << " <option(s)> SOURCES"
//			  << "Options:\n"
//			  << "\t-o,--operation\tThe operation want to execute:\n"
//			  << "\t\t\t\'generate\' for generating graph\n"
//			  << "\t\t\t\'simulate\' for simulate tolerance strategy.\n"
//			  << "\t-t,--topology\tThe type of graph for network topology\n"
//			  << "\t-s,--strategy\tSpecify the evaluated topology\n"
//			  << std::endl;
//}

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
		return K11;
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

void generateGraph(int argc, char* argv[])
{
	if (argc < 10)
	{
		show_missing_generate_arguments(9);
	}
	else
	{
		ByzantineSimulator* sim = new ByzantineSimulator();
		sim->GenerateNetwork(GetDeployingType(argv[3]), atoi(argv[4]), atoi(argv[8]), argv[9],
				atof(argv[5]), atof(argv[6]), atof(argv[7]), 1);
		delete sim;
//		showArgumentDebugGenerateGraph(argv);
	}
}

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
						manager->RunSimulation(GetDeployingType(argv[3]),
								GetToleranceType(argv[4]), atoi(argv[5]),
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
//	if (argc < 2)
//	{
//		show_usage(argv[1]);
//	}
//	else
//	{
//		if (strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "generate") == 0)
//		{
//			generateGraph(argc, argv);
//		}
//		else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "simulate") == 0)
//		{
//			runSimulation(argc, argv);
//		}
//	}
//	SimulatorManager* manager = new SimulatorManager();
//	manager->RunOneStepSimulation(ER_Random, K01, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/10/1000",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/K01_0", 2, 100);
//	manager->RunOneStepSimulation(ER_Random, CxHop, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/10/1000",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/CxHop_0", 2, 100);
//	manager->RunOneStepSimulation(ScaleFree, K01, 10000, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/2000",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/8/2000", 2, 100);
//	manager->RunOneStepSimulation(ScaleFree, K01, 10000, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/3000",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/8/3000", 2, 100);
//	manager->RunOneStepSimulation(ScaleFree, K01, 10000, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/4000",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/8/4000", 2, 100);

	SimulatorManager* manager = new SimulatorManager();
//	manager->ReadOneStepResults(ER_Random, K01, "/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/K01_0",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/K01_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ER_Random, CxHop, "/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/CxHop_0",
//				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/10/1000/CxHop_0.out", 0, 0.01);
	manager->ReadOneStepResults(ER_Random, C01K03, "/Users/thanhnd/Workspace/Results/Erdos_Renyi/14/1000/CxHop_0",
				"/Users/thanhnd/Workspace/Results/Erdos_Renyi/14/1000/CxHop_0.out", 0, 0.01);

//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/3000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/4000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/4000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/5000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/5000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/6000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/6000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/7000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/7000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/8000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/8000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/9000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/9000/C01K03_0.out", 0, 0.01);
//	manager->ReadOneStepResults(ScaleFree, C01K03, "/Users/thanhnd/Workspace/Results/ScaleFree/10000/C01K03_0",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/10000/C01K03_0.out", 0, 0.01);
//	manager->ReadResults(ScaleFree, K03, "/Users/thanhnd/Workspace/Results/ScaleFree/K3",
//				"/Users/thanhnd/Workspace/Results/ScaleFree/K03.out", 50);

//	ByzantineSimulator* sim = new ByzantineSimulator();
//	sim->Convert2HopInformation(ER_Random, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/14/10000",
//			"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/14/advanced/10000", 101);
//	sim->Convert2HopInformation(ER_Random, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/5/5000",
//			"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/5/advanced/5000", 101);
//	sim->Convert2HopInformation(ER_Random, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/5/10000",
//			"/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/5/advanced/10000", 101);

//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/1000", 7, 1000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/2000", 7, 2000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/3000", 7, 3000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/4000", 7, 4000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/5000", 7, 5000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/6000", 7, 6000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/7000", 7, 7000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/8000", 7, 8000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/9000", 7, 9000, 4);
//	sim->GenerateScaleFreeNetwork(101, "/Users/thanhnd/Workspace/Results/Graphs/ScaleFree/8/10000", 7, 10000, 4);
//	sim->GenerateER_RandomNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Erdos_Renyi/10/1000", 0.01);
}
