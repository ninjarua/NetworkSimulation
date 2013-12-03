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

//int BinarySearchN(int searchItem, int a[], int n)
//{
//	int left = 0;
//	int right = n - 1;
//	int mid;
//	while (left < right)
//	{
//		mid = (left + right) / 2;
//		if (a[mid] == searchItem)
//			return mid;
//		else if (a[mid] >= a[left] && searchItem >= a[left] && searchItem < a[mid])
//			right = mid - 1;
//		else if (a[mid] >= a[left] && (searchItem < a[left] || searchItem > a[mid]))
//			left = mid + 1;
//		else if (a[mid] <= a[left] && searchItem < a[left] && searchItem > a[mid])
//			left = mid + 1;
//		else if (a[mid] <= a[left] && (searchItem >= a[left] || searchItem < a[mid]))
//			right = mid - 1;
//	}
//	return -1;
//}

int main(int argc, char* argv[])
{
//	int a[10] = {5, 6, 7, 8, 9, 0, 1, 2, 3, 4};
//	cout << BinarySearchN(9, a, 10);
	//cout << makeChange(100, 25);
	//srand(time(NULL)); // Set random seed for random procedure

	SimulatorManager* manager = new SimulatorManager();
//	manager->runOneStepSimulation(Small_world, CBridges, 10000, 0, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/10_5/1000",
//			"/Users/thanhnd/Workspace/Results/Smallworld/10_5/1000/CBridges_0", 1, 100);

//	manager->readOneStepResults(FixedRange, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_0\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_0\\10000\\CCo1E_0.out", 0, 0.01);
	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_1\\10000\\CCo1E_0",
				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_1\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_2\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_2\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_3\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_3\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_4\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_4\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_5\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_5\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_6\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_6\\10000\\CCo1E_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, CCo1E, "d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_8\\10000\\CCo1E_0",
//				"d:\\Workspace\\Programming\\results\\Smallworld\\8\\8_8\\10000\\CCo1E_0.out", 0, 0.01);

//	manager->addOneStepSimulation(Small_world, K1Hop, 1, 10000, 0, "", "", 100, 100);
//	manager->addOneStepSimulation(Small_world, CCo1E, 1, 10000, 0.25, "", "", 100, 100);
//	manager->addSimulation(Small_world, CCo2E, 1, 10000, "", "", 50, 100);
//	manager->addOneStepSimulation(Small_world, K1Hop, 1, 10000, 0, "", "", 100, 100);
//	manager->addOneStepSimulation(Small_world, CCo1E, 1, 10000, 0.25, "", "", 100, 100);
//	manager->addSimulation(Small_world, KSelf, 1, 10000, "", "", 50, 100);
//
//	manager->addOneStepSimulation(Small_world, K1Hop, 1, 10000, 0, "", "", 100, 100);
//	manager->addSimulation(Small_world, KSelf, 1, 10000, "", "", 50, 100);
//	manager->runSimulationsTest(250, 1);
//	manager->readOneStepResults(Small_world, CCo2E, "/Users/thanhnd/Workspace/server/Results/Smallworld/10_3/4000/CBridges_0",
//				"/Users/thanhnd/Workspace/server/Results/Smallworld/10_3/4000/CBridges_0.out", 0, 0.01);
//	manager->readOneStepResults(Small_world, KSelf, "/Users/thanhnd/Workspace/server/Results/Smallworld/10_1/4000/KSelf_0",
//				"/Users/thanhnd/Workspace/server/Results/Smallworld/10_1/4000/KSelf_0.out", 0, 0.01);

//	manager->readOneStepResults(Small_world, KSelf, "/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0",
//				"/Users/thanhnd/Workspace/Results/Smallworld/14_5/25/1000/K01_0.out", 0, 0.01);

//	SimulatorBase* sim = new SimulatorBase();
//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/1000", 16, 19, 1.01, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateFixedRangeNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/4000", 30, 40, 0.99, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateFixedRangeNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/10_0/10000", 55, 56, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateFixedRangeNetwork(1, 1000000, "D:\\Workspace\\Programming\\results\\test\\1000000", 550, 560, 1, 0.001);	// 16x19, 30x40, 55x56
//	sim->generateSmallworldNetwork(1, 90000, "D:\\Workspace\\Programming\\results\\test\\90000", 10, 1, 165, 170, 1.003, 0.0001);	// 16x19, 30x40, 55x56

//	SimulatorBase* sim = new SimulatorBase();
//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/6/6_0/1000", 22, 23, 1.001, 0.001);	// 22x23, 45x45, 72x72
//	sim->generateFixedRangeNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/6/6_0/4000", 45, 45, 0.995, 0.001);	// 22x23, 45x45, 72x72
//	sim->generateFixedRangeNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/6/6_0/10000", 72, 72, 1.001, 0.001);	// 22x23, 45x45, 72x72

//	SimulatorBase* sim = new SimulatorBase();
//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/8/8_0/1000", 19, 20, 1.005, 0.0001);	// 19x20, 39x39, 62x62
//	sim->generateFixedRangeNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/8/8_0/4000", 39, 39, 0.995, 0.0001);	// 19x20, 39x39, 62x62
//	sim->generateFixedRangeNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/8/8_0/10000", 62, 62, 0.998, 0.0001);	// 19x20, 39x39, 62x62

//	sim->generateFixedRangeNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/1000", 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateFixedRangeNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/4000", 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateFixedRangeNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/10000", 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79

//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/1000", 5, 1, 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/4000", 5, 1, 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/10000", 5, 1, 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79
//	cout << endl;
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/1000", 5, 2, 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/4000", 5, 2, 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/10000", 5, 2, 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79
//	cout << endl;
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/1000", 5, 3, 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/4000", 5, 3, 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/10000", 5, 3, 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79
//	cout << endl;
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/1000", 5, 4, 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/4000", 5, 4, 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/10000", 5, 4, 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79
//	cout << endl;
//	sim->generateSmallworldNetwork(101, 1000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/1000", 5, 5, 24, 25, 0.994, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 4000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/4000", 5, 5, 49, 50, 0.996, 0.0001);	// 24x25, 49x50, 79x79
//	sim->generateSmallworldNetwork(101, 10000, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/10000", 5, 5, 79, 79, 1.003, 0.0001);	// 24x25, 49x50, 79x79
//	cout << endl;

//	SimulatorManager* manager = new SimulatorManager();
//	manager->convert2HopInformation(FixedRange, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_0/1000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_1/1000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_2/1000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_3/1000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_4/1000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/1000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_5/1000", 100, true);
//
//	manager->convert2HopInformation(FixedRange, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_0/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_1/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_2/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_3/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_4/4000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/4000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_5/4000", 100, true);
//
//	manager->convert2HopInformation(FixedRange, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_0/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_0/10000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_1/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_1/10000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_2/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_2/10000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_3/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_3/10000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_4/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_4/10000", 100, true);
//	manager->convert2HopInformation(Small_world, "/Users/thanhnd/Workspace/Results/Graphs/Smallworld/5/5_5/10000",
//				"/Users/thanhnd/Workspace/Results/Graphs/Smallworld/advanced/5/5_5/10000", 100, true);
}

