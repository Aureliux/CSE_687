//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Main.cpp
//Omar Vargas, Huiying Wu

#include <iostream>
#include <string>
#include "Workflow.h"
#include "FileManager.h"
#include <thread>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::thread;

int main(void) {

	string inputpath, temppath, outputpath;
	Workflow workflow;
	vector<string> textlines;
	vector<thread> mappers, reducers;
	thread mapper1, mapper2, mapper3;
	FileManager filemanager;
	int R = 0, Remainder = 0;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	textlines = workflow.partition(inputpath);		// Return vector of all lines of text across all input files.
	R = textlines.size();
	Remainder = R % 3;


	if (Remainder != 0)
	{
		for (int i = 0; i <= R; i + 3)
		{
			if (i < R / 3)
			{
				mapper1(Workflow::mapworkflow, inputpath, temppath, textlines[i]);
			}
			else if (i >= R / 3 && i < R * (2 / 3))
			{
				mapper2.join();
			}
			else if (i >= R * (2 / 3) && i < R)
			{
				mapper3.join();
			}

			workflow.mapworkflow(inputpath, temppath, textlines[i]);
		}

	}
	else
	{
		// Add to last mapper
	}





	// Reducers wait for Mappers to be done.
	for (int i = 0; i <= R; i++)
	{
		// In Work ...
		reducers[i];
		workflow.reduceworkflow(temppath, outputpath, currentfile);
	}

	return 0;
}
