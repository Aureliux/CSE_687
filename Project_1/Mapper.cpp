#include "Mapper.h"

/*	Receives an input file name and line and returns a temporary file containing
	a key-value pair of each word in the file followed by a count of 1.	*/
string Mapper::map(string filename, string fileline)
{
	string currentword;
	string cleanstring;
	string mappedstring;
	char letter;				// Holds the current letter.
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

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

	for (int i = 0; i <= cleanstring.length(); i++)
	{
		letter = cleanstring[i];
		if (letter == ' ')
		{
			
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