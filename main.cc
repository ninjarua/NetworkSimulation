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

static void show_usage(string name)
{
	std::cerr << "Usage: " << name << " <option(s)> SOURCES"
			  << "Options:\n"
			  << "\t-o,--operation\tThe operation want to execute:\n"
			  << "\t\t\t\'generate\' for generating graph\n"
			  << "\t\t\t\'simulate\' for simulate tolerance strategy.\n"
			  << "\t-t,--topology\tThe type of graph for network topology\n"
			  << "\t-s,--strategy\tSpecify the evaluated topology\n"
			  << std::endl;
}

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
		sim->GenerateNetwork(GetDeployingType(argv[3]), atoi(argv[4]), atof(argv[5]), atof(argv[6]),
				atof(argv[7]), 1, atoi(argv[8]), argv[9]);
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
	ByzantineSimulator* sim = new ByzantineSimulator();
	sim->RunSimulation(TorusGrid, K01, 10000, "10000", "Results", 0, 0, 0, 1, 0.01, 0.01, 1, 10000);
}
