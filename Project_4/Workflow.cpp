//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
//Workflow Class
//Omar Vargas, Huiying Wu

#include "Workflow.h"

FileManager filemanager;
Sorter sorter;
vector<string> filetext, mappedfile, sortedtext, reducedstring;

typedef void (*funcMap)(string, string, string);
typedef void (*funcLeftoverfrombuff)(string, string);
typedef void (*funcReduce)(string, vector<string>);

// Returns the number of R buckets to be used by the mapper and reducer threads.
int Workflow::partition(string inputpath)
{
	int R = filemanager.numberoffiles(inputpath);
	cout << "*******************" << endl;
	cout << "Counting " << R << " Buckets" << endl;
	cout << "*******************" << endl << endl;

	return R;
}

// Calls the Mapper DLL inside a thread.
void Workflow::map_workflow(path inputfilename, string temppath, string filename) {
	string fileline, mappedstring;
	filetext = filemanager.opentxtfile(inputfilename);
	cout << "*******************" << endl;
	cout << "...Reading Files..." << endl;
	cout << "*******************" << endl << endl;

	filemanager.createtempfile(temppath, filename);
	HINSTANCE hMapDLL;
	funcMap map;
	funcLeftoverfrombuff leftoverfrombuff;
	const wchar_t* libName = L"MAPLIBRARY";
	hMapDLL = LoadLibraryEx(libName, NULL, NULL);
	if (hMapDLL != NULL) {
		map = (funcMap)GetProcAddress(hMapDLL, "map");
		leftoverfrombuff = (funcLeftoverfrombuff)GetProcAddress(hMapDLL, "leftoverfrombuff");
		if (map != NULL) {
			for (int i = 0; i < filetext.size(); i++) {
				fileline = filetext[i];
				map(temppath, filename, fileline);
			}
		}
		if (leftoverfrombuff != NULL)
			leftoverfrombuff(temppath, filename);
		FreeLibrary(hMapDLL);
	}
	else {
		std::cout << "Map Library load failed!" << std::endl;
	}
}

// Calls the sorter class and Reducer DLL inside a thread.
void Workflow::reduce_workflow(path tempfilepath, string temppath, string sortedfilename, string outputpath) {
	//Call the sorting method to read the mapped text in the temporary directory and perform an alphabetical sort.
	filetext = filemanager.opentxtfile(tempfilepath);

	cout << "*******************" << endl;
	cout << "...Sorting File..." << endl;
	cout << "*******************" << endl << endl;

	sorter.sortfile(tempfilepath, temppath, sortedfilename);

	// Read the sorted text file and send it to the reducer, which will return a reduced text string which is subsequently saved to the output directory.
	sortedtext = filemanager.readsortedfile(temppath, sortedfilename);
	filemanager.createoutputfile(outputpath, "output");

	cout << "*******************" << endl;
	cout << "...Reducing File..." << endl;
	cout << "*******************" << endl << endl;

	HINSTANCE hReduceDLL;
	funcReduce reduce;
	const wchar_t* libName1 = L"REDUCELIBRARY";
	hReduceDLL = LoadLibraryEx(libName1, NULL, NULL);
	if (hReduceDLL != NULL) {
		reduce = (funcReduce)GetProcAddress(hReduceDLL, "reduce");
		if (reduce != NULL)
			reduce(outputpath, sortedtext);
		FreeLibrary(hReduceDLL);
	}
	else {
		cout << "Reduce Library load failed!" << endl;
	}
}