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

	void map(string temppath, string fileline);
	void export_map(string temppath, string str);
};