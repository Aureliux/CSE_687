#include "Workflow.h"

void Workflow::workflow(string inputpath, string temppath, string outputpath)
{
	vector<string> filetext;
	vector<string> mappedfile;
	string fileline;
	string mappedstring;
	vector<string> sortedtext;
	vector<string> reducedstring;
	Mapper mapper;
	Sorter sorter;
	Reducer reducer;
	FileManager filemanager;

	// Send string to the mapper and return a mapped string.
	filetext = filemanager.opentxtfile(inputpath);
	filemanager.createtempfile(temppath);
	cout << "******************" << endl;
	cout << "Reading Files...." << endl;
	cout << "******************" << endl << endl;
	for (int i = 0; i < filetext.size(); i++) {
		fileline = filetext[i];
		mappedstring = mapper.map(inputpath, fileline);
		mappedfile.push_back(mappedstring);
		filemanager.writetotemp(temppath, mappedfile[i]);
	}

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
	filemanager.deletetemp(temppath);
}
	
