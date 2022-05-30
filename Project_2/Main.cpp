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
	vector<string> files;
	vector<thread> mappers, reducers;
	thread mapper1, mapper2, mapper3;
	FileManager filemanager;
	int R=0;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	int R = filemanager.numberoffiles(inputpath);
	files  = workflow.partition(inputpath, R);

	// Call each thread here ...

	for (int i = 0; i <= R; i++)
	{
		// In Work ...
		mappers[i];
		workflow.mapworkflow(inputpath, temppath, files[i]);
	}
	
	
	// Reducers wait for Mappers to be done.
	for (int i = 0; i <= R; i++)
	{
		// In Work ...
		reducers[i];
		workflow.reduceworkflow(temppath, outputpath);
	}

	return 0;
}
