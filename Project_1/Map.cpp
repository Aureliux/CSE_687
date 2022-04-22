#include "FileManager.h"
#include <iostream>
using namespace std;

class Map
{
public:
	// FileManager filemanager;

	/*	Receives an input file name and line and returns a temporary file containing
		a key-value pair of each word in the file followed by a count of 1.	*/
	void map(string filename, string fileline)
	{
		cout << "TESTING"
		
		//char letter;
		string word[]{};
		int count = 0;
		
		if (fileline == NULL)
		{
			// Do nothing.
		}
		else
		{
			while (*fileline)
			{
				// Calculate word count.
				if (*fileline == ' ' || *fileline == '\t' || *fileline == '\n')
				{
					// Do nothing.
				}
				else
				{
					count++;
				}
			}

			cout << "There are " + count + " words.";

			// Remove punctuation, whitespace and capitalization.
			//for (int i = 0; i < count; i++)
			//{
			//	// Send intermediate output to buffer, which is then sent to the output file.
			//	filemanager.buffer_export(word[i], 1);
			//}
		}

		return 0;
	}
};