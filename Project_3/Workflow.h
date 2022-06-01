//Syracuse University
//CSE 687 Object Oriented Design
//Project 3
//Workflow Class
//Omar Vargas, Huiying Wu

#pragma once
#include "Sorter.h"
#include "FileManager.h"
#include <string>
#include <Windows.h>
#include <thread>
#include <filesystem>

using std::string;
using std::vector;
using std::cout;
using std::thread;

class Workflow{
public:
	//void readinputfile(string inputpath);
	static void map_workflow(string inputpath, path inputfilename, string temppath, string filename);
	void reduce_workflow(string temppath, string outputpath);
};