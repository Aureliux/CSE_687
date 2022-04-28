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

	filetext = filemanager.opentxtfile(inputpath);
	filemanager.createtempfile(temppath);
	cout << "******************" << endl;
	cout << "Reading File...." << endl;
	for (int i = 0; i < filetext.size(); i++){
		fileline = filetext[i];
		// cout << "Current Line: " << fileline << endl;

		// Send string to the mapper and return a mapped string.
		mappedstring = mapper.map(inputpath, fileline);
		mappedfile.push_back(mappedstring);
		// cout << mappedfile[i] << endl;
		// cout << "Mapped Line: " << mappedfile[i] << endl;
		filemanager.writetotemp(temppath, mappedfile[i]);
	}

	filetext = filemanager.opentxtfile(temppath);
	// Send string to the sorter and return a sorted string.
	cout << "******************" << endl;
	cout << "Sorting File...." << endl;
	sorter.sortfile(temppath);
	// sortedtext = filemanager.readsortedfile();
	// cout << "Sorted Text: " << endl << sortedtext << endl;

	filetext = filemanager.readsortedfile(temppath);
	// Send string to the reducer and return a reduced string.

	reducedstring = reducer.reduce(filetext);

	cout << "******************" << endl;
	cout << "Outputing File...." << endl;
	cout << "******************" << endl;
	filemanager.createoutputfile(outputpath);
	for (int i = 0; i < reducedstring.size(); i++){
		filemanager.writetooutput(outputpath, reducedstring[i]);
	}
}
	
