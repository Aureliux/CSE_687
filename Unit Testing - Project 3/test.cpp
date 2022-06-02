#include "pch.h"
#include "..\Project_3\FileManager.h"
#include "..\Project_3\Sorter.h"
#include "..\Project_3\Workflow.cpp"
#include "..\Project_3\FileManager.cpp"
#include "..\Project_3\Sorter.cpp"

TEST(FileManagerTest, tempfilecreate) {
	FileManager filemanager;
	string filename = "tempfile";
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createtempfile(temp, filename);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), true);
}

TEST(FileManagerTest, sortedfilecreate) {
	FileManager filemanager;
	string filename = "sorted";
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.createsortedfile(temp, filename);
	ASSERT_EQ(exists(temp + "\\sorted.txt"), true);
}

TEST(FileManagerTest, deleteempfiles) {
	FileManager filemanager;
	string temp = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	filemanager.deletetemp(temp);
	ASSERT_EQ(exists(temp + "\\tempfile.txt"), false);
}