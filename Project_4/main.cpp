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

	// Testing in Omar's PC
	/*inputpath = "C:\\Users\\aurel\\source\\repos\\CSE_687\\Input_Text";
	temppath = "C:\\Users\\aurel\\source\\repos\\CSE_687\\Temp_Text";
	outputpath = "C:\\Users\\aurel\\source\\repos\\CSE_687\\Output_Text";*/

	// Testing in Huiying's PC
	inputpath = "C:\\Users\\Joann\\Desktop\\test\\shakespeare";
	temppath = "C:\\Users\\Joann\\Desktop\\test\\Temp";
	outputpath = "C:\\Users\\Joann\\Desktop\\test\\Output";

	R = workflow.partition(inputpath); // Returns the number of R buckets to be used by the mapper and reducer threads.
	txtname = fm.txtname(inputpath); // Return the full path name for each file in the input directory.

	//Stub 1 - Mapper
	// Initialize WinSock
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(wVersion, &wsadata) != 0) {
		std::cerr << "Can't Initialize winsock!" << endl;
		return -1;
	}

	// Creating stub1 socket
	SOCKET stub1 = socket(AF_INET, SOCK_STREAM, 0);
	if (stub1 == INVALID_SOCKET) {
		std::cerr << "Socket Create Fail " << endl;
		return -1;
	}

	// Fill in information for stub1 socket
	sockaddr_in add;
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	add.sin_port = htons(25000);

	// bind and listen for stub1
	bind(stub1, (sockaddr*)&add, len);
	listen(stub1, SOMAXCONN);

	sockaddr_in controller;
	int controllerSize = sizeof(controller);

	SOCKET Controller_Socket = accept(stub1, (sockaddr*)&controller, &controllerSize);
	if (Controller_Socket == INVALID_SOCKET) {
		std::cerr << "Socket Create Fail " << endl;
		return -1;
	}

	closesocket(stub1);

	char stub1_buf[256] = { 0 };
	int msg_resv = recv(Controller_Socket, stub1_buf, 256, 0);
	if (msg_resv == SOCKET_ERROR) {
		std::cerr << "Error in recv()" << endl;
	}
	if (msg_resv != 0) {
		// Mapper Threads
		printf("%s\n", stub1_buf);
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
		send(Controller_Socket, "Stub1: Mapper Complete..\n", strlen("Stub1: Mapper Complete..\n"), 0);
	}







	tempfile = fm.txtname(temppath); // Return the full path name for each file in the temporary directory.

	// Stub 2 - Reducer
	// Initialize WinSock
	WORD wVersion_2 = MAKEWORD(2, 2);
	WSADATA wsadata_2;
	if (WSAStartup(wVersion_2, &wsadata_2) != 0) {
		std::cerr << "Can't Initialize winsock!" << endl;
		return -1;
	}
	// Creating stub2 socket
	SOCKET stub2 = socket(AF_INET, SOCK_STREAM, 0);
	if (stub2 == INVALID_SOCKET) {
		std::cerr << "Socket Create Fail " << endl;
		return -1;
	}

	// Fill in information for stub2 socket
	sockaddr_in add_2;
	int len_2 = sizeof(sockaddr_in);
	add_2.sin_family = AF_INET;
	add_2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	add_2.sin_port = htons(25000);

	// bind and listen for stub2
	bind(stub2, (sockaddr*)&add_2, len_2);
	listen(stub2, SOMAXCONN);

	sockaddr_in controller_2;
	int controllerSize_2 = sizeof(controller_2);

	SOCKET Controller_Socket_2 = accept(stub2, (sockaddr*)&controller_2, &controllerSize_2);
	if (Controller_Socket_2 == INVALID_SOCKET) {
		std::cerr << "Socket Create Fail " << endl;
		return -1;
	}

	closesocket(stub2);

	char stub2_buf[256] = { 0 };
	int msg_resv_2 = recv(Controller_Socket_2, stub2_buf, 256, 0);
	if (msg_resv_2 == SOCKET_ERROR) {
		std::cerr << "Error in recv()" << endl;
	}
	if (msg_resv_2 != 0) {
		// Reducer Threads
		printf("%s\n", stub2_buf);
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
		send(Controller_Socket_2, "Stub2: Reducer Complete..\n", strlen("Stub2: Reducer Complete..\n"), 0);
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

	closesocket(Controller_Socket);
	closesocket(Controller_Socket_2);
	WSACleanup();

	return 0;
}