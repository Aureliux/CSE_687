//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//Workflow Class
//Omar Vargas, Joanna
#include "Workflow.h"

// Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.
void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	FileManager filemanager;
	Mapper mapper;
	Sorter sorter;
	Reducer reducer;
	vector<string> filetext, mappedfile, sortedtext, reducedstring;
	string fileline, mappedstring;

	// Read text files from the input directory, send each line to the mapper, and return a mapped string to the temporary directory.
	cout << "******************" << endl;
	cout << "Reading Files...." << endl;
	cout << "******************" << endl << endl;
	filetext = filemanager.opentxtfile(inputpath);
	filemanager.createtempfile(temppath);
	for (int i = 0; i < filetext.size(); i++) {
		fileline = filetext[i];
		mapper.map(temppath, fileline);
	}
	mapper.leftoverfrombuff(temppath);

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
	reducedstring = reducer.reduce(sortedtext);
	filemanager.createoutputfile(outputpath, "\\output.txt");
	for (int i = 0; i < reducedstring.size(); i++){
		filemanager.writetooutput(outputpath, "\\output.txt", reducedstring[i]);
	}
	
	// Create a success file once the Map-Reduce operation is completed.
	filemanager.createoutputfile(outputpath, "\\success.txt");
	filemanager.writetooutput(outputpath, "\\success.txt", "SUCCESS");
	filemanager.deletetemp(temppath);
}