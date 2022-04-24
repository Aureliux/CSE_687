#include "FileManager.h"

vector<string> opentxtfile(string pathway) {
	vector<string> txtdata;
	string line;
	path str(pathway);
	if (!exists(str))
		exit(EXIT_FAILURE);
	directory_entry entry(str);
	directory_iterator b(pathway), e;
	vector<path> txt_file(b, e);
	ifstream opentxt;
	for (int i = 0; i < txt_file.size(); i++)
	{
		opentxt.open(txt_file[i]);
		if (opentxt) {
			while (getline(opentxt, line))
			{
				txtdata.push_back(line);
			}
		}
	}
	return txtdata;
}
