#include "pch.h"
#include "..\Project_1\Workflow.h"
#include "..\Project_1\FileManager.h"
#include "..\Project_1\Mapper.h"
#include "..\Project_1\Sorter.h"
#include "..\Project_1\Reducer.h"
#include "..\Project_1\Workflow.cpp"
#include "..\Project_1\FileManager.cpp"
#include "..\Project_1\Mapper.cpp"
#include "..\Project_1\Sorter.cpp"
#include "..\Project_1\Reducer.cpp"

TEST(workflowTest, pathway) {
	Workflow workflow;
	string input = "C:\\Users\\Joann\\Desktop\\test\\Input";
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	string output = "C:\\Users\\Joann\\Desktop\\test\\Output";
	workflow.workflow(input, temp, output);
	ASSERT_EQ(exists(output + "\\SUCCESS.txt"), true);
}
TEST(filemanagerTest, tempfilecreate) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createtempfile(temp);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), true);
}

TEST(filemanagerTest, sortedfilecreate) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createsortedfile(temp);
	ASSERT_EQ(exists(temp + "\\sorted.txt"), true);
}

TEST(mapperTest, mapperoutput) {
	FileManager filemanager;
	Mapper map;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	vector<string> str;
	str.push_back("project, 1");
	str.push_back("one, 1");
	str.push_back("hello, 1");
	str.push_back("world, 1");
	map.export_map(temp, str);
	vector<string> file_v = filemanager.readtempfile(temp);
	ASSERT_EQ((file_v[0] == "project, 1"), true);
}

TEST(sorterTest, sortedTest) {
	FileManager filemanager;
	Sorter sorter;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	string sorted = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	sorter.sortfile(temp);
	vector<string> sortedfile_v = filemanager.readsortedfile(sorted);
	ASSERT_EQ((sortedfile_v[0] == "hello, 1"), true);
}

TEST(reducerTest, sortedTest) {
	FileManager filemanager;
	Reducer reducer;
	string line;
	vector<string> str;
	str.push_back("hello, 1");
	str.push_back("hello, 1");
	str.push_back("hello, 1");
	str.push_back("hello, 1");
	str.push_back("one, 1");
	str.push_back("project, 1");
	str.push_back("world, 1");
	str.push_back("zoom, 1");
	vector<string> output_v = reducer.reduce(str);
	ASSERT_EQ((output_v[0] == "hello, 1, 1, 1, 1"), true);
}

TEST(FileManagerTest, deleteempfiles) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.deletetemp(temp);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), false);
}
