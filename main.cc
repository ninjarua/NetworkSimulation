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
		//cout << sim->GenerateNetwork(FixedRange, 1000, 3000, 7500, 330, 10, 100, "FixedRange");
		sim->RunSimulation(FixedRange, K01, "FixedRange", 10000, 0, 0, 0, 0.99, 0.01, 0.01, 100);
	}
	catch (std::exception& ex)
	{
		cout << "Got " << ex.what() << endl;
	}
}
