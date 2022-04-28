#include "Reducer.h"

vector<string> Reducer::reduce(vector<string> sortedtext){
	for (int i = 0; i < sortedtext.size(); i++){
		int v_size = sortedtext.size();
		int dup_word = 0;
		int j = i + 1;
		while (j < sortedtext.size() && sortedtext[i] == sortedtext[j]){
			sortedtext.erase(remove(sortedtext.begin() + i + 1, sortedtext.end(), sortedtext[j]), sortedtext.end());
			dup_word = v_size - sortedtext.size();
			j++;
		}
		while (dup_word > 0){
			sortedtext[i].append(", 1");
			dup_word--;
		}
	}
	return sortedtext;
}