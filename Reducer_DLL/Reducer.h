//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//Reduce Class
//Omar Vargas, Huiying Wu
#pragma once
#ifdef REDUCERDLL_EXPORTS
#define REDUCERDLL_API __declspec(dllexport)
#else
#define REDUCERDLL_API __declspec(dllimport)
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

extern "C" REDUCERDLL_API vector<string> reduce(vector<string> sortedtext); // Deletes repeated wordsand appends a "1" to the original word to count how many times it was repeated.
