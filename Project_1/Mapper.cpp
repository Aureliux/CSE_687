#include "Mapper.h"
#include <iostream>
#include <string>
using namespace std;

/*	Receives an input file name and line and returns a temporary file containing
	a key-value pair of each word in the file followed by a count of 1.	*/
string Mapper::map(string filename, string fileline)
{
	string currentword;
	string cleanstring;
	string mappedstring;
	// list newlist[]{};		// Holds the new list without punctuation.
	// std::map newmap[][];
	char letter;				// Holds the current letter.
	int start = 0;				// Position to split the words.

	// Removes punctuation from string.
	for (int i = 0; i < fileline.length(); i++)
	{
		letter = fileline[i];
		if (letter != '!' && letter != '?' && letter != '.' &&
			letter != ',' && letter != ':' && letter != ';')
		{
			cleanstring += letter;
		}
	}

	for (int i = 0; i < cleanstring.length(); i++)
	{
		letter = cleanstring[i];
		if (letter == ' ')
		{
			currentword = cleanstring.substr(start, i);
			mappedstring = currentword.append(", 1") + currentword.append("\n");
			start = i;

			cout << currentword << endl;
			cout << mappedstring << endl;
		}
	}

	cout << "Final: " << mappedstring << endl;

	return mappedstring;
}