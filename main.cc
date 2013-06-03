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
#include "ByzantineSimulator.h"
#include "nsException.h"
#include "Logger.h"

using namespace std;
using namespace simulators;

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	srand(time(NULL)); // Set random seed for random procedure
	try
	{
		ByzantineSimulator* sim = new ByzantineSimulator();
//		sim->GetParameters(FixedRange, 1000, 330, 3000, 7500, 10);
		//sim->GetParameters(TorusGrid, 900, 10, 100, 100, 10);
		//cout << sim->DeployNetwork(1, false);
		cout << sim->GenerateNetwork(FixedRange, 1000, 3000, 7500, 330, 10, 100, "fixedRange");
		//sim->RunSimulation(10000, 0.01, 0.01, K01, &PrintToFile, 0, 0, 0.1, 0.2);
	}
	catch (std::exception& ex)
	{
		cout << "Got " << ex.what() << endl;
	}
}
