#include "Mapper.h"

FileManager filemanager;
int buffer_size = 30;
vector<string> map_v;


/*	Receives an input file name and line and returns a temporary file containing
	a key-value pair of each word in the file followed by a count of 1.	*/
void Mapper::map(string temppath, string fileline)
{
	string currentword, cleanstring, mappedstring;
	vector<string> mappedfile;
	char letter;				// Holds the current letter.
	int start = 0;				// Start position to split the words.
	int end = 0;				// End position to split the words.

	// Removes punctuation and capitalization from string.
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
	map_v.push_back(mappedstring);
	if (map_v.size() == buffer_size){
		export_map(temppath, map_v);
		map_v.clear();
	}
}

void Mapper::leftoverfrombuff(string temppath){
	export_map(temppath, map_v);
}

void Mapper::export_map(string temppath, vector<string> str_v){
	for (int i = 0; i < str_v.size(); i++){
		filemanager.writetotemp(temppath, str_v[i]);
	}
}