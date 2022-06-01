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
#include <chrono>
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
		mtx.lock();
		threads.push_back(thread(&Workflow::map_workflow, txtname[i], temppath, "temp" + std::to_string(num)));
		std::this_thread::sleep_for(std::chrono::seconds(1));
		num = 2 + i;
		mtx.unlock();
	}

	for (int i = 0; i < numoffile; i++) {
		threads[i].join();
	}

	return 0;
}