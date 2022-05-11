#include "pch.h"
#include "..\Project_2\FileManager.h"
#include "..\Project_2\Sorter.h"
#include "..\Project_2\Workflow.cpp"
#include "..\Project_2\FileManager.cpp"
#include "..\Project_2\Sorter.cpp"

TEST(workflowTest, pathway) {
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

TEST(FileManagerTest, deleteempfiles) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.deletetemp(temp);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), false);
}