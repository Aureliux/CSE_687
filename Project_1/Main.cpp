#include <iostream>
#include <string>
#include <algorithm>
#include "Workflow.h"
using namespace std;

string convertpath(string path){
{
    while((pos=path.find_first_of('\\',pos))!=string::npos){
        path.insert(pos, "\\");
        pos=pos+2;
    }
    return path;
}

int main(void){
	
	string inputpath;
	string temppath;
	string outputpath;

	Workflow workflow;

	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);
	
	inputpath = convertpath(inputpath);
	temppath = convertpath(temppath);
	outputpath = convertpath(outputpath);

	workflow.workflow(inputpath, temppath, outputpath);		// Call workflow class and pass the file paths.

}
