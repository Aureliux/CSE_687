//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//Workflow Class
//Omar Vargas, Huiying Wu

#include "Workflow.h"
#include "windows.h"

typedef vector<string> (*funcmap)(string, string);
typedef vector<string> (*funcreduce)(string, string);

// Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.
void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	HINSTANCE hDLL1;
	HINSTANCE hDLL2;
	funcmap map = nullptr;
	funcreduce reduce = nullptr;
	const wchar_t* libName1 = L"MAPPER_DLL";
	const wchar_t* libName2 = L"REDUCER_DLL";

	hDLL1 = LoadLibraryEx(libName1, NULL, NULL);
	hDLL2 = LoadLibraryEx(libName2, NULL, NULL);

	FileManager filemanager;
	// Mapper mapper;
	Sorter sorter;
	// Reducer reducer;
	vector<string> filetext, mappedfile, sortedtext, reducedstring, map_v;
	string fileline, mappedstring;

	if (hDLL1 != NULL && hDLL2 != NULL) {

		// Read text files from the input directory, send each line to the mapper, and return a mapped string to the temporary directory.
		cout << "******************" << endl;
		cout << "Reading Files...." << endl;
		cout << "******************" << endl << endl;
		filetext = filemanager.opentxtfile(inputpath);
		filemanager.createtempfile(temppath);
		for (int i = 0; i < filetext.size(); i++) {
			fileline = filetext[i];
			map_v = map(temppath, fileline);
			filemanager.export_map(temppath, map_v);
		}
		// map_v = ;
		filemanager.leftoverfrombuff(temppath, map_v);

		// Call the sorting method to read the mapped text in the temporary directory and perform an alphabetical sort.
		filetext = filemanager.opentxtfile(temppath);
		cout << "******************" << endl;
		cout << "Sorting File...." << endl;
		cout << "******************" << endl << endl;
		sorter.sortfile(temppath);

		// Read the sorted text file and send it to the reducer, which will return a reduced text string which is subsequently saved to the output directory.
		sortedtext = filemanager.readsortedfile(temppath);
		cout << "******************" << endl;
		cout << "Reducing File...." << endl;
		cout << "******************" << endl << endl;
		reducedstring = reduce(sortedtext);
		filemanager.createoutputfile(outputpath, "\\output.txt");
		for (int i = 0; i < reducedstring.size(); i++) {
			filemanager.writetooutput(outputpath, "\\output.txt", reducedstring[i]);
		}

		// Create a success file once the Map-Reduce operation is completed.
		filemanager.createoutputfile(outputpath, "\\success.txt");
		filemanager.writetooutput(outputpath, "\\success.txt", "SUCCESS");
		filemanager.deletetemp(temppath);
	}
	else {
		std::cout << "Library load failed!" << std::endl;
	}
}