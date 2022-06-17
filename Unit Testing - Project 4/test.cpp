#include "pch.h"
#include "..\Project_4\FileManager.h"
#include "..\Project_4\Sorter.h"
#include "..\Project_4\Workflow.cpp"
#include "..\Project_4\FileManager.cpp"
#include "..\Project_4\Sorter.cpp"

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

TEST(SorterTest, sortedtext) {
	FileManager filemanager;
	Sorter sorter;
	path temppath = "C:\\Users\\Joann\\Desktop\\sorter_testing\\abc.txt";
	string temp = "C:\\Users\\Joann\\Desktop\\sorter_testing";
	sorter.sortfile(temppath, temp, "sorted");
	vector<string> sortedfile_v = filemanager.readsortedfile(temp, "sorted");
	ASSERT_EQ((sortedfile_v[0] == "aa"), true);

}