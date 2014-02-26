/*
 * NetworkGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "NetworkGenerator.h"

namespace generators {

NetworkGenerator::NetworkGenerator() {
}

NetworkGenerator::~NetworkGenerator() {
	// TODO Auto-generated destructor stub
}

bool NetworkGenerator::generateFromFiles(Network* network, string folder, int index)
{
	string filename = getFilenameByDeployment(folder, index);
	if (filename == "")
		return false;
	ifstream f(filename.c_str(), ifstream::in);
	//cout << filename << endl;
	f >> (*network);
	if (deployment->using2HopInfo && (!network->has2HopInfo || network->diameter == 0))
		network->createAdvancedInformation();
	f.close();
	return true;
}

string NetworkGenerator::getDeployingName()
{
	return deployment->getDeployingName();
}

void NetworkGenerator::switch2HopInfo(bool using2HopInfo)
{
	deployment->using2HopInfo = using2HopInfo;
}

string NetworkGenerator::getFilename(int id)
{
	string filename("graph");
	if (id > 0)
	{
		char number[6];
		sprintf(number, "_%04d", id);
		filename = filename + number;
	}
	filename = filename + ".out";
	return filename;
}

string NetworkGenerator::getVerifyFilename(int id)
{
	char number[18];
	sprintf(number, "%04d_verified.out", id);
	string filename("graph_");
	filename = filename + number;
	return filename;
}

string NetworkGenerator::getFailureString(int count)
{
	string results("Cannot create all graphs!\n");
	results = results + "Only create";
	char number[5];
	sprintf(number, "%04d", count);
	results = results + number;
	return results;
}

string NetworkGenerator::getFilenameByDeployment(string folder, int number)
{
	string filename(deployment->getDeployingName() + "_" + getFilename(number));
	filesystem::path dir(folder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(folder + OS_SEP + filename);
//	cout << file.string() << Constants::endline;
//	if (!filesystem::exists(file))
//	{
//		return "";
//	}
	return file.string();
}

string NetworkGenerator::generateToFiles(Network* network, string folder, int times, bool create2HopInfo)
{
	for (int i = 0; i < times; i++)
	{
		bool hasTopology = deployment->runDeploy(network);
		if (hasTopology)
		{
			if (create2HopInfo && !network->has2HopInfo)
				network->createAdvancedInformation();
			Logger::Write(network, getFilenameByDeployment(folder, i));
			//if (drawNetwork)
			network->calculateAverageDegree();
			cout << network->avgDegree << endl;
		}
		else
		{
			return getFailureString(i);
		}
	}
	return "Success";
}

void NetworkGenerator::writeNetworkToFile(Network* network, string folder, int index)
{
	Logger::Write(network, getFilenameByDeployment(folder, index));
}

} /* namespace generators */
