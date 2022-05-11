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
	void workflow(string inputpath, string temppath, string outputpath); /* Calls the FileManager class to handle file operations and the Mapper,
																			Sorter, and Reducer classes to handle the modification algorithms. */
};
