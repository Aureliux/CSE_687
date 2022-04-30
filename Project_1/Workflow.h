#pragma once
#include "FileManager.h"
#include "Mapper.h"
#include "Sorter.h"
#include "Reducer.h"
#include <string>
using namespace std;

class Workflow
{
public:
	
	void workflow(string inputpath, string temppath, string outputpath); /* Calls the FileManager class to handle file operations and the Mapper,
																			Sorter, and Reducer classes to handle the modification algorithms. */
};