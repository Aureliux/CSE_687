#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "filemanager.h"
using namespace std;


class Mapper
{
public:
	void export_map(string temppath, vector<string> str_v);
	void map(string temppath, string fileline);
	void leftoverfrombuff(string pathway);

};