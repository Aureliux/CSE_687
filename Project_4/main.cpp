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

	// Client Socket Declarations
	WSADATA wsaData;
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(25000);

	// wVersionRequested Error Checking
	WORD wVersionRequested = MAKEWORD(2, 2);
	//  if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	//  {
	//  	cout << "Could not find a usable version of Winsock.dll" << endl;
	//  	WSACleanup();
	//  	return 1;
	//  }
	//  else
	//  	cout << "The Winsock 2.2 dll was found okay" << endl;

	// WSA Startup
	err = WSAStartup(wVersionRequested, &wsaData);
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

	// write()



	// Stub proccess (thread) that uses server sockets.
	
	// START STUBS (THREADS) FOR MAPPER AND REDUCER
	// ...

	// Creating Server Socket
	SOCKET serverlisten1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverlisten1 == INVALID_SOCKET) {
		cout << "Socket function failed with error : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}

	// Server Socket Declarations
	sockaddr_in serverService;
	serverService.sin_family = AF_INET;
	serverService.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverService.sin_port = htons(26000);

	// Binding Server Socket
	err = bind(serverlisten1, (SOCKADDR*)&serverService, sizeof(serverService));
	if (err == SOCKET_ERROR)
	{
		cout << "Binding failed with error: " << WSAGetLastError() << endl;
		err = closesocket(serverlisten1);
		if (err == SOCKET_ERROR)
		{
			cout << "closesocket function failed with error: " << WSAGetLastError() << endl;
		}
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Bind succesful!" << endl;
	}

	// Listening for incoming request
	err = listen(serverlisten1, SOMAXCONN) == SOCKET_ERROR;
	if (err == SOCKET_ERROR)
	{
		cout << "Listening failed with error: " << WSAGetLastError() << endl;
		err = closesocket(serverlisten1);
		if (err == SOCKET_ERROR)
		{
			cout << "closesocket function failed with error: " << WSAGetLastError() << endl;
		}
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Listening..." << endl;
	}

	// Accepting incoming connection
	SOCKET serveraccept1 = accept(serverlisten1, NULL, NULL);
	if (serveraccept1 == INVALID_SOCKET)
	{
		cout << "Accept failed with error: " << WSAGetLastError() << endl;
		err = closesocket(serverlisten1);
		if (err == SOCKET_ERROR)
		{
			cout << "closesocket function failed with error: " << WSAGetLastError() << endl;
		}
		WSACleanup();
		return 1;
	}
	else
	{
		cout << "Accepting..." << endl;

		
		// read() for instruction telling to start child processes
			// Create child threads for mapper
			// Call Mapper DLL
			// Send heartbeat message at k seconds(?) to client.
	}

	// SECOND STUB PROCCESS FOR REDUCER
		// CREATE SOCKETS, BIND, LISTEN, ACCEPT
				// read() for instruction telling to start child processes
				// Create child threads for reducer
				// Controller (client) says when to call Reducer DLL


	closesocket(serverlisten1);
	WSACleanup();
	// END STUB (THREAD)


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