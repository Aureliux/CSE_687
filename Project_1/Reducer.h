#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Reducer
{
public:
	vector<string> reduce(vector<string> sortedtext); // Deletes repeated wordsand appends a "1" to the original word to count how many times it was repeated.
};