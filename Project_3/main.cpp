//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Main.cpp
//Omar Vargas, Huiying Wu

#include <iostream>
#include <string>
#include <thread>
#include <mutex> 
#include <filesystem>
#include "Workflow.h"
#include "FileManager.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::thread;
std::mutex mtx;

Workflow workflow;
FileManager filemgr;

int main(void) {

	vector<string> alltext;
	vector<path> txtname;
	string inputpath, temppath, outputpath;
	int numoffile = 0, threadSpread = 0, begin = 0;
	int num = 1;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);
	
	numoffile = filemgr.numberoffile(inputpath);
	txtname = filemgr.txtname(inputpath);

	vector<thread> threads;
	for (int i = 0; i < numoffile; i++){
		threads.push_back(thread(&Workflow::map_workflow, inputpath, txtname[i], temppath, "temp" + std::to_string(num)));
		//cout << i << std::this_thread::get_id << endl;
		num = 2 + i;
	}

	for (int i = 0; i < numoffile; i++) {
		threads[i].join();
	}

	return 0;
}