//Syracuse University
//CSE 687 Object Oriented Design
//Project 4
//Main.cpp
//Omar Vargas, Huiying Wu

#define WIN32_LEAN_AND_MEAN

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
	int R = 0, num = 1, num_2 = 1;

	// Client Socket Declarations
	WSADATA wsaData;
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(25000);

	// wVersionRequested Error Checking
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		cout << "Could not find a usable version of Winsock.dll" << endl;
		WSACleanup();
		return 1;
	}
	else
		cout << "The Winsock 2.2 dll was found okay" << endl;

	// WSA Startup and Error Checking
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		cout << "WSAStartup failed with error: " << err << endl;
		return 1;
	}

	// Creating Client Socket
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		cout << "Socket function failed with error : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	// Connecting Client Socket
	err = connect(client, (SOCKADDR*)&clientService, sizeof(clientService));
	if (err == SOCKET_ERROR)
	{
		cout << "Connection failed with error: " << WSAGetLastError() << endl;
		err = closesocket(client);
		if (err == SOCKET_ERROR)
		{
			cout << "closesocket function failed with error: " << WSAGetLastError() << endl;
		}
		WSACleanup();
		return 1;
	}


	// Stub proccesses (threads) that will use server sockets.

	// Create socket
	SOCKET server1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Bind socket
	int bind(server1, *name, namelen);

	// Listen for incoming requests
	int listen(server1, backlog);

	// Accept incoming connection
	SOCKET accept(server1, *addr, *addrlen);






	// Prompt user to designate the input, temporary, and output directories.
	cout << "Please enter input file path:" << endl;
	getline(cin, inputpath);
	cout << "Please enter temporary file path:" << endl;
	getline(cin, temppath);
	cout << "Please enter output file path:" << endl;
	getline(cin, outputpath);

	R = workflow.partition(inputpath); // Returns the number of R buckets to be used by the mapper and reducer threads.
	txtname = fm.txtname(inputpath); // Return the full path name for each file in the input directory.

	// Mapper Threads
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

	tempfile = fm.txtname(temppath); // Return the full path name for each file in the temporary directory.

	// Reducer Threads
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

	WSACleanup();
	return 0;
}