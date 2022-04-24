#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

using namespace std;
using namespace std::filesystem;


class FileManager
{
public:
	vector<string> opentxtfile(string pathway);
	void createtempfile(string pathway);
	void writetotemp(string pathway, string mappedstring);
	void createoutputfile(string pathway);
	void writetooutput(string pathway, string outputstring);
	void deletetemp(string pathway);
};
