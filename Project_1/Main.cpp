#include <iostream>
#include "Workflow.h"
using namespace std;

int main(void){
	
	string inputpath;
	string temppath;
	string outputpath;

	Workflow workflow;

	cout << "Please enter input file path:" << endl;
	cin >> inputpath;
	cout << "Please enter temporary file path:" << endl;
	cin >> temppath;
	cout << "Please enter output file path:" << endl;
	cin >> outputpath;


	workflow(inputpath, temppath, outputpath);		// Call workflow class and pass the file paths.

}