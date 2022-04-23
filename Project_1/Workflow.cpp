#include "Workflow.h"
#include "FileManager.h"
#include "Mapper.h"
#include "Sorter.h"
#include "Reducer.h"

void workflow(string inputpath, string temppath, string outputpath)
{
	string fileline;
	string mappedstring;
	string sortedstring;
	string reducedstring;
	Mapper mapper;
	// Sorter sorter;
	// Reducer reducer;

	FileManager filemanager;
		
	// Read one line from a file in the input folder.
	fileline = filemanager(inputpath);

	// Send string to the mapper and return a mapped string.
	mappedstring = mapper.map(inputpath, fileline);

	// Send string to the sorter and return a sorted string.
	// sortedstring = sorter.sort(inputpath, mappedstring);

	// Send string to the reducer and return a reduced string.
	// reducedstring = reducer.reduce(inputpath, sortedstring);

}