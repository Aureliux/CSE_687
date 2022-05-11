//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//MapLibrary DLL
//Omar Vargas, Huiying Wu

#include "pch.h"
#include "framework.h"
#include "MapLibrary.h"

int buffer_size = 30;
vector<string> map_v;

void map(string temppath, string fileline)
{
	string currentword, cleanstring, mappedstring;
	vector<string> mappedfile;
	string token;
	char letter;				// Holds the current letter.
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

	// Removes punctuation and capitalization from each line of the input text.
	boost::tokenizer<> tok(fileline);
	for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
		token = *beg;
		boost::algorithm::to_lower(token);
		token += ", 1";
		map_v.push_back(token);
		if (map_v.size() == buffer_size) {
			export_map(temppath, map_v);
			map_v.clear();
		}
	}
}

void leftoverfrombuff(string temppath) {
	export_map(temppath, map_v);
}

void export_map(string temppath, vector<string> str_v) {
	std::ofstream tempfile;
	tempfile.open(temppath + "\\tempfile.txt", std::ios_base::app);
	for (int i = 0; i < str_v.size(); i++) {
		tempfile << str_v[i] << "\n";
	}
	tempfile.close();
}