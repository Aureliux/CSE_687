//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//Workflow Class
//Omar Vargas, Huiying Wu

#pragma once
#include "Sorter.h"
#include "FileManager.h"
#include <string>
#include <Windows.h>

using std::string;
using std::vector;
using std::cout;

class Workflow
{
public:
	
	/* Splits input into R buckets */
	int partition(string inputpath);
	
	/* Each thread calls the FileManager class to handle file operations and
	the Mapper DLL to handle the mapping algorithms. */
	void mapworkflow(string inputpath, string temppath, int R);

	/* Each thread calls the FileManager class to handle file operations and
	the Sorter followed by the Reducer DLL to handle the reducing algorithms. */
	void reduceworkflow(string temppath, string outputpath);	

};
