//Syracuse University
//CSE 687 Object Oriented Design
//Project 1
//Map Class
//Omar Vargas, Huiying Wu

#include "framework.h"
#include "pch.h"
#include "Mapper.h"

// FileManager filemanager;
// int buffer_size = 30;
vector<string> map_v;

/*	Receives a temporary directory path and text line and returns a modified string containing
	a key-value pair of each word in the file followed by a count of 1.	*/
vector<string> map(string temppath, string fileline)
{
	string currentword, cleanstring, mappedstring;
	vector<string> mappedfile;
	char letter;				// Holds the current letter.
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

	// Removes punctuation and capitalization from each line of the input text.
	for (int i = 0; i < fileline.length(); i++) {
		letter = fileline[i];
		if (letter != '!' && letter != '?' && letter != '.' && letter != ','
			&& letter != ':' && letter != ';' && letter != '\"'
			&& letter != '\'' && letter != '&' && letter != '-' 
			&& letter != '\n' && letter != '\0') {
			letter = tolower(letter);
			cleanstring += letter;
		}
	}

	// Split the words of the input text file.
	for (int i = 0; i <= cleanstring.length(); i++) {
		letter = cleanstring[i];
		if (letter == ' ') {
				end = i - start;
				currentword = cleanstring.substr(start, end);
				currentword = currentword.append(", 1");
				mappedstring += currentword;
				if (i == 0) {
					start = i;
				}
				else {
					mappedstring.append("\n");
					start = i + 1;
				}
			}
		if (i == cleanstring.length()) {
				end = i - start;
				currentword = cleanstring.substr(start, end);
				currentword = currentword.append(", 1");
				mappedstring += currentword;
			}
	}

	// Send the mapped lines to a string vector based on a preset buffer size.
	map_v.push_back(mappedstring);
	//if (map_v.size() == buffer_size){
	//	export_map(temppath, map_v);
	//	map_v.clear();
	//}

	return map_v;
}

//// Send the leftover buffer lines to the mapped string vector.
//MAPPERDLL_API void leftoverfrombuff(string temppath){
//	export_map(temppath, map_v);
//}
//
//// Write the mapped string vector into a file in the temporary directory.
//MAPPERDLL_API void export_map(string temppath, vector<string> str_v){
//	for (int i = 0; i < str_v.size(); i++){
//		filemanager.writetotemp(temppath, str_v[i]);
//	}
//}