#include "Workflow.h"

void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	Mapper mapper;
	Sorter sorter;
	Reducer reducer;
	FileManager filemanager;
	Mapper map;
	vector<string> filetext, mappedfile, sortedtext, reducedstring;
	string fileline, mappedstring;


	// Send string to the mapper and return a mapped string.
	cout << "******************" << endl;
	cout << "Reading Files...." << endl;
	cout << "******************" << endl << endl;
	filetext = filemanager.opentxtfile(inputpath);
	filemanager.createtempfile(temppath);
	for (int i = 0; i < filetext.size(); i++) {
		fileline = filetext[i];
		map.map(temppath, fileline);
	}
	map.leftoverfrombuff(temppath);

	// Send string to the sorter and return a sorted string.
	filetext = filemanager.opentxtfile(temppath);
	cout << "******************" << endl;
	cout << "Sorting File...." << endl;
	cout << "******************" << endl << endl;
	sorter.sortfile(temppath);

	// Send string to the reducer and return a reduced string.
	sortedtext = filemanager.readsortedfile(temppath);
	cout << "******************" << endl;
	cout << "Reducing File...." << endl;
	cout << "******************" << endl << endl;
	reducedstring = reducer.reduce(sortedtext);
	filemanager.createoutputfile(outputpath, "\\output.txt");
	for (int i = 0; i < reducedstring.size(); i++){
		filemanager.writetooutput(outputpath, "\\output.txt", reducedstring[i]);
	}
	
	// Create additional success file.
	filemanager.createoutputfile(outputpath, "\\success.txt");
	filemanager.writetooutput(outputpath, "\\success.txt", "SUCCESS");
	//filemanager.deletetemp(temppath);
}
	
