//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Workflow Class
//Omar Vargas, Huiying Wu

#include "Workflow.h"

FileManager filemanager;
Sorter sorter;

vector<string> filetext, mappedfile, sortedtext, reducedstring;

typedef void (*funcMap)(string, string, string);
typedef void (*funcLeftoverfrombuff)(string, string);
typedef void (*funcReduce)(string, vector<string>);

// Determines the number of R buckets and returns the R value.
int Workflow::partition(string inputpath)
{
	int R = filemanager.numberoffile(inputpath);
	cout << "*******************" << endl;
	cout << "...Counting " << R << " Buckets..." << endl;
	cout << "*******************" << endl << endl;

	return R;
}

void Workflow::map_workflow(path inputfilename, string temppath, string filename){
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



// Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.
void Workflow::reduce_workflow(path tempfilepath, string temppath, string sortedfilename, string outputpath){
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
	// Create a success file once the Map-Reduce operation is completed.
	filemanager.createoutputfile(outputpath, "\\success");
	filemanager.writetooutput(outputpath, "\\success", "SUCCESS");
	cout << "*******************" << endl;
	cout << "......SUCCESS......" << endl;
	cout << "*******************" << endl << endl;
}