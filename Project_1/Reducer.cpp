#include "Reducer.h"

string Reducer::reduce(string filename, vector<string> sortedtext)
{
	string reducedstring;

	for (int i = 0; i < sortedtext.size() - 1; i++)
	{
		while (sortedtext[i] == sortedtext[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) + 1])
		{
			sortedtext[i].append(", 1");
			remove(sortedtext.begin(), sortedtext.end(), sortedtext[i + 1]);
		}
	}

	for (int i = 0; i <= sortedtext.size(); i++)
	{
		reducedstring += sortedtext[i];
	}

	return reducedstring;
}