//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Workflow Class
//Omar Vargas, Huiying Wu

#include "Workflow.h"

FileManager filemanager;
Sorter sorter;

typedef void (*funcMap)(string, string, string);
typedef void (*funcLeftoverfrombuff)(string);
typedef void (*funcReduce)(string, vector<string>);

// Splits input into R buckets and returns the R value.
vector<string> Workflow::partition(string inputpath)
{
	// int R = filemanager.numberoffiles(inputpath);
	// cout << "*******************" << endl;
	// cout << "...Dividing into " << R << " Buckets..." << endl;
	// cout << "*******************" << endl << endl;

	vector<string> textlines;
	textlines = filemanager.opentxtfile(inputpath);
	
	return textlines;
}

// Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.
void Workflow::mapworkflow(string inputpath, string temppath, string textline)
{
	vector<string> filetext, mappedfile, sortedtext, reducedstring;
	string mappedstring, filename;
	
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
			//for (int i = 0; i < filetext.size(); i++) {
				//fileline = filetext[i];
				map(temppath, filename, textline);
			//}
		}
		if (leftoverfrombuff != NULL)
			leftoverfrombuff(temppath);
		FreeLibrary(hMapDLL);
	}
	else {
		std::cout << "Map Library load failed!" << std::endl;
	}
}

void Workflow::reduceworkflow(string temppath, string outputpath, string textline)
{
	vector<string> filetext, mappedfile, sortedtext, reducedstring;
	string fileline, mappedstring, filename;
	
	//Call the sorting method to read the mapped text in the temporary directory and perform an alphabetical sort.
	filetext = filemanager.opentxtfile(temppath);

	cout << "*******************" << endl;
	cout << "...Sorting File..." << endl;
	cout << "*******************" << endl << endl;

	sorter.sortfile(temppath, textline);

	// Read the sorted text file and send it to the reducer, which will return a reduced text string which is subsequently saved to the output directory.
	sortedtext = filemanager.readsortedfile(temppath);
	filemanager.createoutputfile(outputpath, "\\output.txt");

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
	// Create a success file once the Map-Reduce operation is completed.
	filemanager.createoutputfile(outputpath, "\\success.txt");
	filemanager.writetooutput(outputpath, "\\success.txt", "SUCCESS");
	filemanager.deletetemp(temppath);
	cout << "*******************" << endl;
	cout << "......SUCCESS......" << endl;
	cout << "*******************" << endl << endl;
}
