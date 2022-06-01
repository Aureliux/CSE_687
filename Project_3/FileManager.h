//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//File Management Class
//Omar Vargas, Huiying Wu

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std::filesystem;
using std::string;
using std::vector;
using std::ifstream;
using std::fstream;
using std::cin;
using std::cout;
using std::endl;


class FileManager
{
public:
	vector<path> txtname(string pathway);
	vector<string> opentxtfile(string pathway); // Read all the text files in the input directory and save each line to vector.
	int numberoffile(string pathway); // Return the number of file in that input directory.

	void createtempfile(string pathway, string filename); // Create a temp.txt to be save temporary result from mapper.

	void createsortedfile(string pathway); // Create sorted.txt to save sorted data.
	vector<string> readtempfile(string pathway, string filename); // Read temporary file for the Sorter class.
	void writetosortedfile(string pathway, string mappedstring); // Write to sorted file.

	void createoutputfile(string pathway, string filename); // Create output.txt to save the final result.
	vector<string> readsortedfile(string pathway); // Read sorted file for the Reducer class.
	void writetooutput(string pathway, string filename, string outputstring); // Write to output file.

	void deletetemp(string pathway); // Delete temporary file and sorted file after the final result is saved to the output file.
};