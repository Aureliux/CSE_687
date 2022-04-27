#include "Reducer.h"

string Reducer::reduce(string filename, vector<string> sortedtext)
{
	string reducedstring;
	cout << sortedtext[0] << endl; // CRASHING HERE!
	cout << "REACHED HERE!" << endl;

	for (vector<int>::size_type i = 0; i < sortedtext.size(); i++)
	{
		while (sortedtext[i] == sortedtext[i + 1])
		{
			sortedtext[i].append(", 1");
			remove(sortedtext.begin(), sortedtext.end(), sortedtext[i + 1]);
		}
	}

	for (vector<int>::size_type i = 0; i <= sortedtext.size(); i++)
	{
		reducedstring += sortedtext[i];
	}

	return reducedstring;
}