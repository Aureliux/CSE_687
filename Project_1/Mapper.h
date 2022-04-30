#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "filemanager.h"
using namespace std;

class Mapper
{
public:
	void export_map(string temppath, vector<string> str_v);		/*	Receives a temporary directory path and text line and returns a modified string containing
																a key-value pair of each word in the file followed by a count of 1.	*/
	void map(string temppath, string fileline);					// Send the leftover buffer lines to the mapped string vector.
	void leftoverfrombuff(string pathway);						// Write the mapped string vector into a file in the temporary directory.

};