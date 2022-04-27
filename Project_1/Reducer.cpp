#include "Reducer.h"

string Reducer::reduce(string filename, vector<string> sortedtext)
{
	string reducedstring;

	for (int i = 0; i < sortedtext.size() - 1; i++){
		if (sortedtext[i] == sortedtext[i + 1]) {
			sortedtext[i].append(", 1");
			remove(sortedtext.begin(), sortedtext.end(), sortedtext[i]);
		}
	}

	for (vector<int>::size_type i = 0; i <= sortedtext.size(); i++){
		reducedstring += sortedtext[i];
	}

	return reducedstring;
}