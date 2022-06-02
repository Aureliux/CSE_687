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
	vector<path> txtname, tempfile;
	string inputpath, temppath, outputpath;
	int numoffile = 0;
	int num = 1, num_2 = 1;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);
	
	numoffile = filemgr.numberoffile(inputpath);
	txtname = filemgr.txtname(inputpath);

	vector<thread> map_threads;
	for (int i = 0; i < numoffile; i++){
		mtx.lock();
		map_threads.push_back(thread(&Workflow::map_workflow, txtname[i], temppath, "temp" + std::to_string(num_2)));
		std::this_thread::sleep_for(std::chrono::seconds(2));
		num_2 = 2 + i;
		mtx.unlock();
	}

	for (int i = 0; i < numoffile; i++) {
		map_threads[i].join();
	}

	tempfile = filemgr.txtname(temppath);
	vector<thread> reduce_threads;
	for (int i = 0; i < numoffile; i++) {
		mtx.lock();
		reduce_threads.push_back(thread(&Workflow::reduce_workflow, tempfile[i], temppath, "sortedfile" + std::to_string(num), outputpath));
		std::this_thread::sleep_for(std::chrono::seconds(2));
		num = 2 + i;
		mtx.unlock();
	}

	for (int i = 0; i < numoffile; i++) {
		reduce_threads[i].join();
	}

	return 0;
}