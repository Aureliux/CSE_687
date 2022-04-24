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
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

	// cout << "Initial String: " << fileline << endl;
	// cout << "Initial Length: " << fileline.length() << endl;

	// Removes punctuation and capitalization from string.
	for (int i = 0; i < fileline.length(); i++)
	{
		letter = fileline[i];
		if (letter != '!' && letter != '?' && letter != '.' &&
			letter != ',' && letter != ':' && letter != ';')
		{
			if (isupper(letter))
			{
				letter = tolower(letter);
			}
			cleanstring += letter;
		}
	}
	// cout << "Clean String: " << cleanstring << endl;
	// cout << "Clean Length: " << cleanstring.length() << endl;

	for (int i = 0; i <= cleanstring.length(); i++)
	{
		letter = cleanstring[i];
		if (letter == ' ')
		{
			cout <<"i: " << i << endl;
			cout << "Start: " << start << endl;
			cout << "End: " << end << endl;
			
			end = i - start;
			currentword = cleanstring.substr(start, end);
			currentword = currentword.append(", 1");
			mappedstring += currentword;
			if (i == 0)
			{
				start = i;
			}
			else
			{
				mappedstring.append("\n");
				start = i + 1;
			}

			cout << "Current Word: " << currentword << endl;
			cout << "Interim String: " << mappedstring << endl;
		}
		if (i == cleanstring.length())
		{
			end = i - start;
			currentword = cleanstring.substr(start, end);
			currentword = currentword.append(", 1");
			mappedstring += currentword;
		}
	}

	/*	The map() function will call a second function export that takes a key and value as two parameters.
		The export function will buffer output in memory and periodically write the data out to disk (periodicity
		can be based on the size of the buffer). The intermediate data will be written to the temporary directory
		(specified via command line). */

	// Logic here

	return mappedstring;
}