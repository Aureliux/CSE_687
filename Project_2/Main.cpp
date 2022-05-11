//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//Main.cpp
//Omar Vargas, Huiying Wu

#include <iostream>
#include <string>
#include "Workflow.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(void) {

	string inputpath, temppath, outputpath;
	Workflow workflow;

	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	// Call Workflow class and pass the user-designated file paths.
	workflow.workflow(inputpath, temppath, outputpath);

	return 0;
}
