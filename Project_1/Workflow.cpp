#include "Workflow.h"
#include "FileManager.h"
#include "Mapper.h"
#include "Sorter.h"
#include "Reducer.h"
#include "Filemanager.h"
using namespace std;

void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	vector<string> filetext;
	vector<string> mappedfile;
	string fileline;
	string mappedstring;
	string sortedstring;
	string reducedstring;
	Mapper mapper;
	Sorter sorter;
	Reducer reducer;
	FileManager filemanager;

	// FileManager filemanager;

	// Read one line from a file in the input folder.
	// fileline = filemanager(inputpath);

	// TESTING
	filetext = filemanager.opentxtfile(inputpath);

	for (int i = 0; i < filetext.size(); i++)
	{
		fileline = filetext[i];

		// Send string to the mapper and return a mapped string.
		mappedstring = mapper.map(inputpath, fileline);
		mappedfile[i] = mappedstring;
		cout << "Mapped Line: " << mappedfile[i] << endl;

		// Send string to the sorter and return a sorted string.
		sortedstring = sorter.sort(inputpath, mappedstring);
		// cout << "Sorted String: " << sortedstring << endl;

		// Send string to the reducer and return a reduced string.
		reducedstring = reducer.reduce(inputpath, sortedstring);
		// cout << "Reduced String: " << reducedstring << endl;
	}

	// cout << "Mapped File: " << mappedfile << endl;
}
	
