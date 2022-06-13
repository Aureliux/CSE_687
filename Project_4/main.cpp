//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
//Main.cpp
//Omar Vargas, Huiying Wu

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include <sys/types.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "Workflow.h"
#include "FileManager.h"

#pragma comment(lib, "ws2_32.lib")

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::thread;
std::mutex mtx;

Workflow workflow;
FileManager fm;


int main(void) {

	vector<string> alltext, outputtxt, temp_v;
	vector<path> txtname, tempfile, outputfile;
	string inputpath, temppath, outputpath;
	int R = 0, num = 1, num_2 = 1, err = 0;

	//cout << "Please enter input file path:" << endl;
	//getline(cin, inputpath);
	//cout << "Please enter temporary file path:" << endl;
	//getline(cin, temppath);
	//cout << "Please enter output file path:" << endl;
	//getline(cin, outputpath);

	inputpath = "C:\\Users\\Joann\\Desktop\\test\\shakespeare";
	temppath = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	outputpath = "C:\\Users\\Joann\\Desktop\\test\\Output";

	//Stub 1
	R = workflow.partition(inputpath); // Returns the number of R buckets to be used by the mapper and reducer threads.
	txtname = fm.txtname(inputpath); // Return the full path name for each file in the input directory.
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(wVersion, &wsadata) != 0) {
		return 1;
	}
	SOCKET stub1 = socket(AF_INET, SOCK_STREAM, 0);
	if (stub1 == INVALID_SOCKET) {
		cout << "Socket Fail " << WSAGetLastError() << endl;
		return -1;
	}
	sockaddr_in add;
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	add.sin_port = htons(25000);

	// Connect to Server Socket
	int i = connect(stub1, (sockaddr*)&add, len);
	if (SOCKET_ERROR == i) {
		return 1;
	}

	// Accept and send data
	char stub_1[256] = { 0 };
	int ret = recv(stub1, stub_1, 256, 0);
	if (ret == 0) {
		return 1;
	}
	else if (ret > 0) {
		// Mapper Threads
		printf("%s\n", stub_1);
		vector<thread> map_threads;
		for (int i = 0; i < R; i++) {
			mtx.lock();
			map_threads.push_back(thread(&Workflow::map_workflow, txtname[i], temppath, "temp" + std::to_string(num_2)));
			std::this_thread::sleep_for(std::chrono::seconds(2));
			num_2 = 2 + i;
			mtx.unlock();
		}

		for (int i = 0; i < R; i++) {
			map_threads[i].join();
		}
		send(stub1, "Stub1: Mapper Complete..\n", strlen("Stub1: Mapper Complete..\n"), 0);
	}


	// Stub 2
	tempfile = fm.txtname(temppath); // Return the full path name for each file in the temporary directory.

	WORD wVersion_2 = MAKEWORD(2, 2);
	WSADATA wsadata_2;
	if (WSAStartup(wVersion_2, &wsadata_2) != 0) {
		return 1;
	}
	SOCKET stub2 = socket(AF_INET, SOCK_STREAM, 0);
	if (stub2 == INVALID_SOCKET) {
		cout << "Socket Fail " << WSAGetLastError() << endl;
		return -1;
	}
	sockaddr_in add_2;
	int len_2 = sizeof(sockaddr_in);
	add_2.sin_family = AF_INET;
	add_2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	add_2.sin_port = htons(25000);

	// Connect to Server Socket
	int j = connect(stub2, (sockaddr*)&add_2, len_2);
	if (SOCKET_ERROR == j) {
		return 1;
	}

	// Accept and send data
	char stub_2[256] = { 0 };
	int ret_2 = recv(stub2, stub_2, 256, 0);
	if (ret_2 == 0) {
		return 1;
	}
	else if (ret_2 > 0) {
		// Mapper Threads
		printf("%s\n", stub_2);
		vector<thread> reduce_threads;
		for (int i = 0; i < R; i++) {
			mtx.lock();
			reduce_threads.push_back(thread(&Workflow::reduce_workflow, tempfile[i], temppath, "sortedfile" + std::to_string(num), outputpath));
			std::this_thread::sleep_for(std::chrono::seconds(2));
			num = 2 + i;
			mtx.unlock();
		}

		for (int i = 0; i < R; i++) {
			reduce_threads[i].join();
		}
		send(stub2, "Stub2: Reducer Complete..\n", strlen("Stub2: Reducer Complete..\n"), 0);
	}


	outputfile = fm.txtname(outputpath);
	for (int i = 0; i < outputfile.size(); i++) {
		outputtxt = fm.readtempfile(outputfile[i]);
		temp_v.insert(temp_v.end(), outputtxt.begin(), outputtxt.end());

	}
	std::sort(temp_v.begin(), temp_v.end());

	fm.deletetemp(outputpath);

	for (int i = 0; i < temp_v.size(); i++) {
		fm.writetooutput(outputpath, "output", temp_v[i]);
	}
	fm.createoutputfile(outputpath, "\\success");
	fm.writetooutput(outputpath, "\\success", "SUCCESS");

	cout << "*******************" << endl;
	cout << "......SUCCESS......" << endl;
	cout << "*******************" << endl << endl;

	fm.deletetemp(temppath); // After reducing, remove files from the temporary directory.

	closesocket(stub1);
	closesocket(stub2);
	WSACleanup();

	return 0;
}