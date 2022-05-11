//Syracuse University
//CSE 687 Object Oriented Design
//Project 2
//ReduceLibrary DLL
//Omar Vargas, Huiying Wu

#include "pch.h"
#include "framework.h"
#include "ReduceLibrary.h"

void reduce(string outputpath, vector<string> sortedtext)
{
	for (int i = 0; i < sortedtext.size(); i++) {
		int v_size = sortedtext.size();
		int dup_word = 0;
		int j = i + 1;
		while (j < sortedtext.size() && sortedtext[i] == sortedtext[j]) {
			sortedtext.erase(remove(sortedtext.begin() + i + 1, sortedtext.end(), sortedtext[j]), sortedtext.end());
			dup_word = v_size - sortedtext.size();
			j++;
		}
		while (dup_word > 0) {
			sortedtext[i].append(", 1");
			dup_word--;
		}
	}
	export_reduce(outputpath, sortedtext);
}

void export_reduce(string outputpath, vector<string> sortedtext) {
	std::fstream outputfile;
	outputfile.open(outputpath + "\\output.txt", std::ios_base::app);
	for (int i = 0; i < sortedtext.size(); i++) {
		outputfile << sortedtext[i] << "\n";
	}
	outputfile.close();
}