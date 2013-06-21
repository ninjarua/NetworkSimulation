/*
 * NetworkGenerator.cc
 *
 *  Created on: Jun 3, 2013
 *      Author: thanhnd
 */

#include "NetworkGenerator.h"

namespace generators {

NetworkGenerator::NetworkGenerator() {
	// TODO Auto-generated constructor stub

}

NetworkGenerator::~NetworkGenerator() {
	// TODO Auto-generated destructor stub
}

bool NetworkGenerator::GenerateFromFiles(Network* network, string folder, int index)
{
	string filename = GetFilenameByDeployment(folder, index);
	if (filename == "")
		return false;
	ifstream f(filename.c_str(), ifstream::in);
	f >> (*network);
	f.close();
	return true;
}

string NetworkGenerator::GetDeployingName()
{
	return deployment->getDeployingName();
}

string NetworkGenerator::GetFilename(int id)
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

string NetworkGenerator::GetVerifyFilename(int id)
{
	char number[18];
	sprintf(number, "%04d_verified.out", id);
	string filename("graph_");
	filename = filename + number;
	return filename;
}

string NetworkGenerator::GetFailureString(int count)
{
	string results("Cannot create all graphs!\n");
	results = results + "Only create";
	char number[5];
	sprintf(number, "%04d", count);
	results = results + number;
	return results;
}

string NetworkGenerator::GetFilenameByDeployment(string folder, int number)
{
	string filename(deployment->getDeployingName() + "_" + GetFilename(number));
	filesystem::path dir(folder);
	if (!filesystem::exists(dir))
		filesystem::create_directory(dir);
	filesystem::path file(folder + OS_SEP + filename);
	//cout << file.string() << Constants::endline;
//	if (!filesystem::exists(file))
//	{
//		return "";
//	}
	return file.string();
}

string NetworkGenerator::GenerateToFiles(Network* network, string folder, int times)
{
	for (int i = 0; i < times; i++)
	{
		bool hasTopology = deployment->runDeploy(network);
		if (hasTopology)
		{
			Logger::Write(network, GetFilenameByDeployment(folder, i));
			//if (drawNetwork)
		}
		else
		{
			return GetFailureString(i);
		}
	}
	return "Success";
}

void NetworkGenerator::WriteNetworkToFile(Network* network, string folder, int index)
{
	Logger::Write(network, GetFilenameByDeployment(folder, index));
}

} /* namespace generators */
