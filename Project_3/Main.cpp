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
#include <mutex>
#include <functional>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::thread;
using std::mutex;

int main(void) {

	string inputpath, temppath, outputpath;
	Workflow workflow;
	vector<path> textname;
	vector<string> textlines;
	vector<thread> mappers, reducers;
	FileManager filemanager;
	int R = 0, Remainder = 0;
	mutex mtx;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	textname = filemanager.txtname(inputpath);
	textlines = workflow.partition(inputpath);		// Return vector of all lines of text across all input files.
	R = textlines.size();
	Remainder = R % 3;

	// thread mapper1(std::bind(& Workflow::mapworkflow, inputpath, temppath, textlines[0]));
	thread mapper1(std::bind( & Workflow::mapworkflow, std::ref(workflow), inputpath, temppath, textlines[0]));
	mapper1.join();

	//if (Remainder != 0)
	//{
	//	for (int i = 0; i <= R; i + 3)
	//	{
	//		if (i < R / 3)
	//		{
	//			// thread mapper1(Workflow::mapworkflow, ref(inputpath), ref(temppath), ref(textlines[i]));
	//			thread mapper1;
	//			mapper1(Workflow::mapworkflow(inputpath, temppath, textlines[i]));
	//			// mapper1.join();
	//		}
	//		else if (i >= R / 3 && i < R * (2 / 3))
	//		{
	//			// mapper2.join();
	//		}
	//		else if (i >= R * (2 / 3) && i < R)
	//		{
	//			// mapper3.join();
	//		}

	//		workflow.mapworkflow(inputpath, temppath, textlines[i]);
	//	}

	//}
	//else
	//{
	//	// Add to last mapper
	//}

	//// Reducers wait for Mappers to be done.
	//for (int i = 0; i <= R; i++)
	//{
	//	// In Work ...
	//	reducers[i];
	//	workflow.reduceworkflow(temppath, outputpath);
	//}

	return 0;
}
