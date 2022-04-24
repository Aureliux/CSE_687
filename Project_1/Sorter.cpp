#include "Sorter.h"

FileManager filehandler;

void Sorter::sortfile(string temppath)
{
	vector<string> sortstring = filehandler.readtempfile(temppath);
	sort(sortstring.begin(), sortstring.end());
	filehandler.createsortedfile(temppath);
	for (int i = 0; i < sortstring.size(); i++)
	{
		filehandler.writetosortedfile(temppath, sortstring[i]);
	}
}