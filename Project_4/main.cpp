//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
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
FileManager fm;

int main(void) {

	vector<string> alltext, outputtxt, temp_v;
	vector<path> txtname, tempfile, outputfile;
	string inputpath, temppath, outputpath;
	int R = 0, num = 1, num_2 = 1;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	R = workflow.partition(inputpath); // Returns the number of R buckets to be used by the mapper and reducer threads.
	txtname = fm.txtname(inputpath); // Return the full path name for each file in the input directory.

	// Mapper Threads
	vector<thread> map_threads;
	for (int i = 0; i < R; i++) {
		mtx.lock();
		map_threads.push_back(thread(&Workflow::map_workflow, txtname[i], temppath, "temp" + std::to_string(num_2)));
		std::this_thread::sleep_for(std::chrono::seconds(2));
		num_2 = 2 + i;
		mtx.unlock();
	}

	for (int i = 0; i < R; i++) {
		map_threads[i].join();
	}

	tempfile = fm.txtname(temppath); // Return the full path name for each file in the temporary directory.

	// Reducer Threads
	vector<thread> reduce_threads;
	for (int i = 0; i < R; i++) {
		mtx.lock();
		reduce_threads.push_back(thread(&Workflow::reduce_workflow, tempfile[i], temppath, "sortedfile" + std::to_string(num), outputpath));
		std::this_thread::sleep_for(std::chrono::seconds(2));
		num = 2 + i;
		mtx.unlock();
	}

	for (int i = 0; i < R; i++) {
		reduce_threads[i].join();
	}

	outputfile = fm.txtname(outputpath);
	for (int i = 0; i < outputfile.size(); i++) {
		outputtxt = fm.readtempfile(outputfile[i]);
		temp_v.insert(temp_v.end(), outputtxt.begin(), outputtxt.end());

	}
	std::sort(temp_v.begin(), temp_v.end());

	fm.deletetemp(outputpath);

	for (int i = 0; i < temp_v.size(); i++) {
		fm.writetooutput(outputpath, "output", temp_v[i]);
	}
	fm.createoutputfile(outputpath, "\\success");
	fm.writetooutput(outputpath, "\\success", "SUCCESS");

	cout << "*******************" << endl;
	cout << "......SUCCESS......" << endl;
	cout << "*******************" << endl << endl;

	fm.deletetemp(temppath); // After reducing, remove files from the temporary directory.

	return 0;
}