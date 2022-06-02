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
	static void map_workflow(path inputfilename, string temppath, string filename);
	static void reduce_workflow(path tempfilepath, string temppath, string sortedfilename, string outputpath);
};