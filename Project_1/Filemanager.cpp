#include "filemanager.h"

vector<string> FileManager::opentxtfile(string pathway) {
	vector<string> txtdata;
	string line;
	path str(pathway);
	if (!exists(str))
		exit(EXIT_FAILURE);
	directory_entry entry(str);
	directory_iterator b(pathway), e;
	vector<path> txt_file(b, e);
	ifstream opentxt;
	for (int i = 0; i < txt_file.size(); i++){
		opentxt.open(txt_file[i]);
		if (opentxt) {
			while (getline(opentxt, line)){
				txtdata.push_back(line);
			}
		}
	}
	return txtdata;
}

void FileManager::createtempfile(string pathway) {
	fstream tempfile;
	tempfile.open(pathway+"\\tempfile.txt", std::ios_base::out);
	if (!tempfile)
		cout << "File Create Fail!" << endl;
	tempfile.close();
}

void FileManager::writetotemp(string pathway, string mappedstring) {
	ofstream tempfile;
	tempfile.open(pathway + "\\tempfile.txt", std::ios_base::app);
	tempfile << mappedstring << endl;
	tempfile.close();
}

void FileManager::createoutputfile(string pathway) {
	fstream outputfile;
	outputfile.open(pathway + "\\output.txt", std::ios_base::out);
	if (!outputfile)
		cout << "File Create Fail!" << endl;
	outputfile.close();
}

void FileManager::writetooutput(string pathway, string outputstring) {
	fstream outputfile;
	outputfile.open(pathway + "\\output.txt", std::ios_base::app);
	outputfile << outputstring << endl;
	outputfile.close();
}

void FileManager::deletetemp (string pathway) {
	remove(pathway + "\\tempfile.txt");
}

