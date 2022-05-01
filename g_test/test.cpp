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
#include <filesystem>

using namespace std;
using namespace std::filesystem;


TEST(WorkflowTest, pathway) {
	Workflow workflow;
	string input = "C:\\Users\\Joann\\Desktop\\test\\Input";
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	string output = "C:\\Users\\Joann\\Desktop\\test\\Output";
	workflow.workflow(input, temp, output);
	ASSERT_EQ(exists(output + "\\SUCCESS.txt"), true);
}

TEST(FileManagerTest, tempfilecreate) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createtempfile(temp);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), true);
}

TEST(FileManagerTest, sortedfilecreate) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createsortedfile(temp);
	ASSERT_EQ(exists(temp + "\\sorted.txt"), true);
}