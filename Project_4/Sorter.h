//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
//Sorting Class
//Omar Vargas, Huiying Wu

#pragma once
#include "FileManager.h"
#include <algorithm>
#include <filesystem>

class Sorter
{
public:
	void sortfile(path tempfile, string temppath, string sortedfilename); // Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.
};