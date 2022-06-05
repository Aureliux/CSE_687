//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
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
	vector<path> txtname(string pathway); // Return the full path name for each file.
	vector<string> opentxtfile(path pathway); // Read all the text files in the input directory and save each line to vector.
	int numberoffiles(string pathway); // Return the number of files in that input directory.

	void createtempfile(string pathway, string filename); // Create a temp.txt to be save temporary result from mapper.
	void createsortedfile(string pathway, string sortedfilename); // Create sorted.txt to save sorted data.
	vector<string> readtempfile(path pathway); // Read temporary file for the Sorter class.
	void writetosortedfile(string pathway, string sortedfilename, string mappedstring); // Write to sorted file.

	void createoutputfile(string pathway, string filename); // Create output.txt to save the final result.
	vector<string> readsortedfile(string pathway, string filename); // Read sorted file for the Reducer class.
	void writetooutput(string pathway, string filename, string outputstring); // Write to output file.

	void deletetemp(string pathway); // Delete temporary file and sorted file after the final result is saved to the output file.
};