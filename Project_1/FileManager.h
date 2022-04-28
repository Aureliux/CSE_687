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
	vector<string> opentxtfile(string pathway); //Read all the text file in the input directory and save each line to vector.

	void createtempfile(string pathway); //Creat a temp.txt to be save temporary result from mapper.
	void writetotemp(string pathway, string mappedstring); //Write to temp.txt.

	void createsortedfile(string pathway); //Creat a sorted.txt to be save sorted data.
	vector<string> readtempfile(string pathway); //Read temp.txt for sort class
	void writetosortedfile(string pathway, string mappedstring); //Write to sorted.txt.

	void createoutputfile(string pathway, string filename); //Creat a output.txt to be save final result.
	vector<string> readsortedfile(string pathway); //Read sorted.txt for reduce class
	void writetooutput(string pathway, string filename, string outputstring); //Write to output.txt

	void deletetemp(string pathway); //Delete temp.txt after final result save to output.txt
};

