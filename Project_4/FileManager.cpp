//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
//File Management Class
//Omar Vargas, Huiying Wu

#include "FileManager.h"

// Return the full path name for each file.
vector<path> FileManager::txtname(string pathway) {
	vector<string> txtdata;
	string line;

	path txtstr(pathway);
	while (!exists(txtstr)) {
		cout << "The directory you enter does not exist, please re-enter:" << endl;
		getline(cin, pathway);
		path txtstr(pathway);
	}
	directory_entry entry(txtstr);
	directory_iterator b(pathway), e;
	vector<path> txt_file(b, e);
	return txt_file;
}

// Read all the text files in the input directory and save each line to vector.
vector<string> FileManager::opentxtfile(path pathway) {
	vector<string> txtdata;
	string line;
	ifstream opentxt;
	opentxt.open(pathway);
	if (opentxt) {
		while (getline(opentxt, line)) {
			if (!line.empty())
				txtdata.push_back(line); //Push each line from the text file to a vector to pass to the Mapper.
		}
	}
	opentxt.close();
	return txtdata;
}

//Return the number of file in that input directory.
int FileManager::numberoffiles(string pathway) {
	int numoffiles = 0;
	for (const auto& entry : directory_iterator(pathway))
		++numoffiles;
	return numoffiles;
}

// Create a temp.txt to be save temporary result from mapper.
void FileManager::createtempfile(string pathway, string filename) {
	fstream tempfile;

	tempfile.open(pathway + "\\" + filename + ".txt", std::ios_base::out); //Create temp file to stored data.
	while (!tempfile) {
		cout << "The directory you enter does not exist, please re-enter:" << endl;
		getline(cin, pathway);
		tempfile.clear();
		tempfile.open(pathway + "\\" + filename + ".txt", std::ios_base::out);
	}
	tempfile.close();
}

// Create sorted.txt to save sorted data.
void FileManager::createsortedfile(string pathway, string sortedfilename) {
	fstream tempfile;
	tempfile.open(pathway + "\\" + sortedfilename + ".txt", std::ios_base::out);
	if (!tempfile)
		cout << "Sorting File Create Fail!" << endl;
	tempfile.close();
}

// Read temporary file for the Sorter class.
vector<string> FileManager::readtempfile(path pathway) {
	vector<string> tempdata;
	string line;
	ifstream tempfile;

	tempfile.open(pathway);
	if (!tempfile) {
		cout << "Temp File Open Fail!" << endl;
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
void FileManager::writetosortedfile(string pathway, string sortedfilename, string mappedstring) {
	fstream tempfile;

	tempfile.open(pathway + "\\" + sortedfilename + ".txt", std::ios_base::app);
	tempfile << mappedstring << endl;
	tempfile.close();
}

// Create output.txt to save the final result.
void FileManager::createoutputfile(string pathway, string filename) {
	fstream outputfile;

	outputfile.open(pathway + "\\" + filename + ".txt", std::ios_base::out);
	while (!outputfile) {
		cout << "The directory you enter does not exist, please re-enter:" << endl;
		getline(cin, pathway);
		outputfile.clear();
		outputfile.open(pathway + "\\" + filename + ".txt", std::ios_base::out);
	}
	outputfile.close();
}

// Read sorted file for the Reducer class.
vector<string> FileManager::readsortedfile(string pathway, string filename) {
	vector<string> sorteddata;
	string line;
	ifstream sortedfile;

	sortedfile.open(pathway + "\\" + filename + ".txt");
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

//Write to output file.
void FileManager::writetooutput(string pathway, string filename, string outputstring) {
	fstream outputfile;
	outputfile.open(pathway + "\\" + filename + ".txt", std::ios_base::app);
	outputfile << outputstring << endl;
	outputfile.close();
}

// Delete temporary file and sorted file after the final result is saved to the output file.
void FileManager::deletetemp(string pathway) {
	for (const auto& entry : std::filesystem::directory_iterator(pathway))
		std::filesystem::remove_all(entry.path());
}