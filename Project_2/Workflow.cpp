//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//Workflow Class
//Omar Vargas, Huiying Wu

#include "Workflow.h"

FileManager filemanager;
Sorter sorter;

typedef void (*funcMap)(string, string);
typedef void (*funcLeftoverfrombuff)(string);
typedef void (*funcReduce)(string, vector<string>);



// Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.
void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	vector<string> filetext, mappedfile, sortedtext, reducedstring;
	string fileline, mappedstring;

	// Read text files from the input directory, send each line to the mapper, and return a mapped string to the temporary directory.
	filetext = filemanager.opentxtfile(inputpath);
	cout << "*******************" << endl;
	cout << "...Reading Files..." << endl;
	cout << "*******************" << endl << endl;
	filemanager.createtempfile(temppath);
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
				map(temppath, fileline);
			}
		}
		if (leftoverfrombuff != NULL)
			leftoverfrombuff(temppath);
		FreeLibrary(hMapDLL);
	}
	else {
		std::cout << "Map Library load failed!" << std::endl;
	}

	//Call the sorting method to read the mapped text in the temporary directory and perform an alphabetical sort.
	filetext = filemanager.opentxtfile(temppath);

	cout << "*******************" << endl;
	cout << "...Sorting File..." << endl;
	cout << "*******************" << endl << endl;

	sorter.sortfile(temppath);

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
