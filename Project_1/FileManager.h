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
	vector<string> opentxtfile(string pathway); // Read all the text file in the input directory and save each line to vector.
	void createtempfile(string pathway); // Creat a temp.txt to be save temporary result from mapper.
	void writetotemp(string pathway, string mappedstring); // Write to temp.txt.
	void createoutputfile(string pathway); // Creat a output.txt to be save final result.
	void writetooutput(string pathway, string outputstring); // Write to output.txt
	void deletetemp(string pathway); // Delete temp.txt after final result save to output.txt
};

