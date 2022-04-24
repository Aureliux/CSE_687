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
};
