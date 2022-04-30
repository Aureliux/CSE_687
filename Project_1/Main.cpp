#include <iostream>
#include <string>
#include "Workflow.h"
using namespace std;

int main(void){
	
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

}