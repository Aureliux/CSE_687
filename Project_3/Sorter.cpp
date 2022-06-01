//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Sorting Class
//Omar Vargas, Huiying Wu

#include "Sorter.h"

FileManager filehandler;

// Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.
void Sorter::sortfile(string temppath, string textline)
{
	vector<string> sortstring = filehandler.readtempfile(temppath, "temp.txt");
	sort(sortstring.begin(), sortstring.end());
	filehandler.createsortedfile(temppath);
	for (int i = 0; i < sortstring.size(); i++)
	{
		if (sortstring[i] != "\n" || sortstring[i] != "\0") {
			filehandler.writetosortedfile(temppath, sortstring[i]);
		}
	}
}
