#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream filemanager;
void readfile(string filename) {
	filemanager.open(filename, ios::in);
	while (!filemanager){
		cout << "File Failed To Open!" << endl;
		cout << "Please enter file name:" << endl;
		cin >> filename;
		filemanager.open(filename);
	}
}

void wirtefile(string filename) {
	filemanager.open(filename, ios::out);
	while (!filemanager) {
		cout << "File Failed To Create!" << endl;
		cout << "Please enter file name:" << endl;
		cin >> filename;
		filemanager.open(filename);
	}
}

void closefile(string filename) {
	filemanager.close();
}
