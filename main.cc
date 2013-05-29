/*
 * main.cpp
 *
 *  Created on: May 22, 2013
 *      Author: thanh
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "ByzantineSimulator.h"
#include "nsException.h"

using namespace std;
using namespace simulators;

#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	srand(time(NULL)); // Set random seed for random procedure
	try
	{
		ByzantineSimulator* sim = new ByzantineSimulator();
		sim->GetParameters(FixedRange, 1000, 330, 3000, 7500, 10, false);
		//cout << sim->DeployNetwork(10, false);
		cout << sim->GenerateNetworkFromFile(10, false);
	}
	catch (exception& ex)
	{
		cout << "Got " << ex.what() << endl;
	}

}
