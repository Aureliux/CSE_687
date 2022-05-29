//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//Main.cpp
//Omar Vargas, Huiying Wu

#include <iostream>
#include <string>
#include "Workflow.h"
#include <thread>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::thread;

int main(void) {

	string inputpath, temppath, outputpath;
	Workflow workflow;
	// vector<thread> mappers;
	// vector<thread> reducers;
	int R;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	// Splits input into R buckets and returns the R value.
	R = workflow.partition(inputpath);

	//// Produces a mapper thread for each R bucket and calls the Mapper workflow.
	//for (int i = 0; i <= R; i++)
	//{
	//	mappers[i];
	//	workflow.mapworkflow(inputpath, temppath, R);
	//}
	//
	//// Produces a reducer thread for each R bucket and calls the Reducer workflow.
	//for (int i = 0; i <= R; i++)
	//{
	//	reducers[i];
	//	workflow.reduceworkflow(temppath, outputpath);
	//}

	return 0;
}
