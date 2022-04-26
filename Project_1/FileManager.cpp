#include "FileManager.h"

// Read all the text file in the input directory and save each line to vector.
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
	for (int i = 0; i < txt_file.size(); i++)
	{
		opentxt.open(txt_file[i]);
		if (opentxt) {
			while (getline(opentxt, line))
			{
				txtdata.push_back(line);
			}
		}
		opentxt.close();
	}
	return txtdata;
}

// Creat a temp.txt to be save temporary result from mapper.
void FileManager::createtempfile(string pathway) {
	fstream tempfile;
	tempfile.open(pathway + "\\tempfile.txt", std::ios_base::out);
	if (!tempfile) {
		cout << "File Create Fail!" << endl;
		exit(EXIT_FAILURE);
	}
	tempfile.close();
}

// Write to temp.txt from mapper.
void FileManager::writetotemp(string pathway, string mappedstring) {
	fstream tempfile;
	tempfile.open(pathway + "\\tempfile.txt", std::ios_base::app);
	tempfile << mappedstring << endl;
	tempfile.close();
}

// Creat a sorted.txt to be save sorted data.
void FileManager::createsortedfile(string pathway) {
	fstream tempfile;
	tempfile.open(pathway + "\\sorted.txt", std::ios_base::out);
	if (!tempfile)
		cout << "File Create Fail!" << endl;
	tempfile.close();
}

//Read temp.txt for sort class
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

// Write to sorted.txt.
void FileManager::writetosortedfile(string pathway, string mappedstring) {
	fstream tempfile;
	tempfile.open(pathway + "\\sorted.txt", std::ios_base::app);
	tempfile << mappedstring << endl;
	tempfile.close();
}

// Creat a output.txt to be save final result.
void FileManager::createoutputfile(string pathway) {
	fstream outputfile;
	outputfile.open(pathway + "\\output.txt", std::ios_base::out);
	if (!outputfile)
		cout << "File Create Fail!" << endl;
	outputfile.close();
}

// Write to output.txt
void FileManager::writetooutput(string pathway, string outputstring) {
	fstream outputfile;
	outputfile.open(pathway + "\\output.txt", std::ios_base::app);
	outputfile << outputstring << endl;
	outputfile.close();
}

// Delete temp.txt after final result save to output.txt
void FileManager::deletetemp(string pathway) {
	remove(pathway + "\\tempfile.txt");
	remove(pathway + "\\sorted.txt");
}