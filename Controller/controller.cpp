#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main() {

	int valread;
	char stub_1[256];
	char stub_2[256];

	// Initialize WinSock
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersion, &wsaData) != 0) {
		std::cerr << "Can't start Winsock" << std::endl;
		return -1;
	}

	// Creating Controller Socket
	SOCKET controller = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (controller == INVALID_SOCKET) {
		std::cerr << "Socket function failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	// Fill in information
	sockaddr_in add;
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_port = htons(25000);
	add.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	// Connect to stub1
	int stub1_msg = connect(controller, (sockaddr*)&add, len);
	if (stub1_msg == SOCKET_ERROR) {
		std::cerr << "Socket connect failed with error:" << WSAGetLastError() << std::endl;
		closesocket(controller);
		WSACleanup();
		return -1;
	}

	int sendResult = send(controller, "Stub1: Begin Map..\n", strlen("Stub1: Begin Map..\n"), 0);
	std::cout << "Stub1: Mapper Started.." << std::endl;
	if (sendResult != 0) {
		ZeroMemory(stub_1, 256);
		int bytesReceived = recv(controller, stub_1, 256, 0);
		printf("%s\n", stub_1);
	}

	// Connect to stub2
	if (sizeof(stub_1) > 0) {
		int stub2_msg = connect(controller, (sockaddr*)&add, len);
		if (stub2_msg == SOCKET_ERROR) {
			std::cerr << "Socket connect failed with error:" << WSAGetLastError() << std::endl;
			closesocket(controller);
			WSACleanup();
			return -1;
		}

		int sendResult = send(controller, "Stub2: Begin Reduce..\n", strlen("Stub2: Begin Reduce..\n"), 0);
		std::cout << "Stub2: Reducer Started.." << std::endl;
		if (sendResult != 0) {
			ZeroMemory(stub_2, 256);
			int bytesReceived = recv(controller, stub_2, 256, 0);
			printf("%s\n", stub_2);
		}
	}


	//// Waiting for connection from client
	//// Get client's ip and port
	//sockaddr_in caddr;
	//caddr.sin_family = AF_INET;
	//int caddrelen = sizeof(sockaddr_in);

	//SOCKET sclient = accept(controller, (sockaddr*)&caddr, &caddrelen);
	//if (sclient == INVALID_SOCKET) {
	//	closesocket(controller);
	//	WSACleanup();
	//	return -1;
	//}

	//// Send notification to stub1 to begin mapping
	//std::cout << "Stub1: Mapper Started.." << std::endl;
	//send(sclient, "Stub1: Begin Mapping..\n", strlen("Stub1: Begin Mapping..\n"), 0);

	//valread = recv(sclient, buffer, 256, 0);
	//printf("%s\n", buffer);

	//SOCKET sclient_2 = accept(controller, (sockaddr*)&caddr, &caddrelen);
	//if (sclient_2 == INVALID_SOCKET) {
	//	return 1;
	//}

	//if (valread > 0) {
	//	std::cout << "Stub2: Reducer Started.." << std::endl;
	//	send(sclient_2, "Stub2: Begin Reducing..\n", strlen("Stub2: Begin Reducing..\n"), 0);
	//	valread = recv(sclient_2, buffer_2, 256, 0);
	//	printf("%s\n", buffer_2);
	//}

	closesocket(controller);
	WSACleanup();
	return 0;
}
