//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//Workflow Class
//Omar Vargas, Huiying Wu
#pragma once
#include "FileManager.h"
#include "Sorter.h"
#include <string>
using namespace std;

class Workflow
{
public:
	
	void workflow(string inputpath, string temppath, string outputpath); /* Calls the FileManager class to handle file operations and the Mapper,
																			Sorter, and Reducer classes to handle the modification algorithms. */
};