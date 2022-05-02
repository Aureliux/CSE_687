//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//File Management Class
//Omar Vargas, Huiying Wu

#include "FileManager.h"

// Read all the text files in the input directory and save each line to vector.
vector<string> FileManager::opentxtfile(string pathway) {
	vector<string> txtdata;
	string line;

	path txtstr(pathway);
	if (!exists(txtstr))
		exit(EXIT_FAILURE);
	directory_entry entry(txtstr);
	directory_iterator b(pathway), e;
	vector<path> txt_file(b, e);
	ifstream opentxt;
	for (int i = 0; i < txt_file.size(); i++){
		opentxt.open(txt_file[i]);
		if (opentxt) {
			while (getline(opentxt, line)){
				txtdata.push_back(line); //Push each line from the text file to a vector to pass to the Mapper.
			}
		}
		opentxt.close();
	}
	return txtdata;
}

// Create a temp.txt to be save temporary result from mapper.
void FileManager::createtempfile(string pathway) {
	fstream tempfile;

	tempfile.open(pathway + "\\tempfile.txt", std::ios_base::out); //Create temp file to stored data.
	if (!tempfile) {
		cout << "File Create Fail!" << endl;
		exit(EXIT_FAILURE);
	}
	tempfile.close();
}

// Write to temporary file for the Mapper class.
void FileManager::writetotemp(string pathway, string mappedstring) {
	fstream tempfile;

	tempfile.open(pathway + "\\tempfile.txt", std::ios_base::app);
	tempfile << mappedstring << endl; //Will accept a string line from mapper to write out to temp file.
	tempfile.close();
}

// Create sorted.txt to save sorted data.
void FileManager::createsortedfile(string pathway) {
	fstream tempfile;

	tempfile.open(pathway + "\\sorted.txt", std::ios_base::out);
	if (!tempfile)
		cout << "File Create Fail!" << endl;
	tempfile.close();
}

// Read temporary file for the Sorter class.
vector<string> FileManager::readtempfile(string pathway) {
	vector<string> tempdata;
	string line;
	ifstream tempfile;

	tempfile.open(pathway + "\\tempfile.txt");
	if (!tempfile) {
		cout << "File Open Fail!" << endl;
		exit(EXIT_FAILURE);
	}
	while (getline(tempfile, line))
	{
		tempdata.push_back(line);
	}
	tempfile.close();
	return tempdata;
}

// Write to sorted file.
void FileManager::writetosortedfile(string pathway, string mappedstring) {
	fstream tempfile;

	tempfile.open(pathway + "\\sorted.txt", std::ios_base::app);
	tempfile << mappedstring << endl;
	tempfile.close();
}

// Create output.txt to save the final result.
void FileManager::createoutputfile(string pathway, string filename) {
	fstream outputfile;

	outputfile.open(pathway + filename, std::ios_base::out);
	if (!outputfile)
		cout << "File Create Fail!" << endl;
	outputfile.close();
}

// Read sorted file for the Reducer class.
vector<string> FileManager::readsortedfile(string pathway) {
	vector<string> sorteddata;
	string line;
	ifstream sortedfile;

	sortedfile.open(pathway + "\\sorted.txt");
	if (!sortedfile) {
		cout << "File Open Fail!" << endl;
		exit(EXIT_FAILURE);
	}
	while (getline(sortedfile, line))
	{
		sorteddata.push_back(line);
	}
	sortedfile.close();
	return sorteddata;
}

// Write to output file.
void FileManager::writetooutput(string pathway, string filename, string outputstring) {
	fstream outputfile;

	outputfile.open(pathway + filename, std::ios_base::app);
	outputfile << outputstring << endl;
	outputfile.close();
}

// Delete temporary file and sorted file after the final result is saved to the output file.
void FileManager::deletetemp(string pathway) {
	remove(pathway + "\\tempfile.txt");
	remove(pathway + "\\sorted.txt");
}