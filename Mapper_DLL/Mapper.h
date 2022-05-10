//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//Map Class
//Omar Vargas, Huiying Wu
#pragma once
#ifdef MAPPERDLL_EXPORTS
#define MAPPERDLL_API __declspec(dllexport)
#else
#define MAPPERDLL_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

extern "C" MAPPERDLL_API vector<string>* map(string temppath, string fileline);					// Send the leftover buffer lines to the mapped string vector.
//	Receives a temporary directory path and text line and returns a modified string containing a key-value pair of each word in the file followed by a count of 1.
// extern "C" MAPPERDLL_API void export_map(string temppath, vector<string> str_v);
// extern "C" MAPPERDLL_API void leftoverfrombuff(string pathway);							// Write the mapped string vector into a file in the temporary directory.
