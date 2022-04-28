#include "Mapper.h"

/*	Receives an input file name and line and returns a temporary file containing
	a key-value pair of each word in the file followed by a count of 1.	*/
string Mapper::map(string filepath, string fileline)
{
	string currentword;
	string cleanstring;
	vector<string> mappedfile;
	string mappedstring;
	// string bufferedstring;
	// FileManager filemanager;
	// array <string, 99> buffer{};
	char letter;				// Holds the current letter.
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

	// Removes punctuation and capitalization from string.
	for (int i = 0; i < fileline.length(); i++){
		letter = fileline[i];
		if (letter != '!' && letter != '?' && letter != '.' && letter != ',' 
		    && letter != ':' && letter != ';' && letter != '\"' 
		    && letter != '\'' && letter != '&' && letter != '-') {
			if (isupper(letter))
				letter = tolower(letter);
			cleanstring += letter;
		}
	}

	for (int i = 0; i <= cleanstring.length(); i++){
		letter = cleanstring[i];
		if (letter == ' '){
			end = i - start;
			currentword = cleanstring.substr(start, end);
			currentword = currentword.append(", 1");
			mappedstring += currentword;
			if (i == 0){
				start = i;
			}
			else{
				mappedstring.append("\n");
				start = i + 1;
			}
		}
		if (i == cleanstring.length()){
			end = i - start;
			currentword = cleanstring.substr(start, end);
			currentword = currentword.append(", 1");
			mappedstring += currentword;
		}
	}

	/*
	The export function will buffer output in memory and periodically write the data out to disk (periodicity
	can be based on the size of the buffer). The intermediate data will be written to the temporary directory
	(specified via command line).
	*/

	//cout << mappedstring << endl;
	//cout << "REACHED HERE!" << endl;

	//void export_map(string filepath, string mappedstring);
	//{
	//	cout << "ENTERED EXPORT!" << endl;
	//	int j = 0;
	//	for (int i = 0; i < mappedstring.length(); i++) {

	//		j = i;

	//		bufferedstring += mappedstring[i];

	//		// buffer array back to string
	//		//while (j < buffer.size()-1)
	//		//{
	//		//	cout << mappedstring[j] << endl;
	//		//	buffer[j] = mappedstring[j];
	//		//	bufferedstring += buffer[j];
	//		//	j++;
	//		//}

	//		mappedfile.push_back(bufferedstring);
	//		filemanager.writetotemp(temppath, mappedfile[i]);
	//	}
	//}

	return mappedstring;
}
