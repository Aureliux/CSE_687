//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//ReduceLibrary DLL
//Omar Vargas, Huiying Wu

#pragma once

#ifdef REDUCELIBRARY_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::fstream;

extern "C" REDUCELIBRARY_API void reduce(string outputpath, vector<string> sortedtext); /* Deletes repeated words and appends a "1" to the
																						original word to count how many times it was repeated.*/
void export_reduce(string outputpath, vector<string> sortedtext);