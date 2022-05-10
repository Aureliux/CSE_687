#pragma once

#ifdef MAPLIBRARY_EXPORTS
#define MAPLIBRARY_API __declspec(dllexport)
#else
#define MAPLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using std::string;
using std::vector;


extern "C" MAPLIBRARY_API void map(string temppath, string fileline);				// Send the leftover buffer lines to the mapped string vector.
extern "C" MAPLIBRARY_API void leftoverfrombuff(string temppath);					// Write the mapped string vector into a file in the temporary directory.
extern "C" MAPLIBRARY_API void export_map(string temppath, vector<string> str_v);	/*	Receives a temporary directory path and text line and returns a modified string containing
																						a key-value pair of each word in the file followed by a count of 1.	*/