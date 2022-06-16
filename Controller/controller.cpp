#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main() {
	char stub_1[256];
	char stub_2[256];
	int bytesReceived = 0;

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

	// Fill in information for controller socket
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

	int sendResult = send(controller, "Stub1: Begin Mapping..\n", strlen("Stub1: Begin Mapping..\n"), 0);
	std::cout << "Stub1: Mapper Started.." << std::endl;
	ZeroMemory(stub_1, 256);
	bytesReceived = recv(controller, stub_1, 256, 0);
	printf("%s\n", stub_1);


	// Connect to stub2
	if (bytesReceived != 0) {
		SOCKET controller_2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (controller_2 == INVALID_SOCKET) {
			std::cerr << "Socket function failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return -1;
		}
		sockaddr_in add_2;
		int len_2 = sizeof(sockaddr_in);
		add_2.sin_family = AF_INET;
		add_2.sin_port = htons(25000);
		add_2.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		int stub2_msg = connect(controller_2, (sockaddr*)&add_2, len_2);
		if (stub2_msg == SOCKET_ERROR) {
			std::cerr << "Socket connect failed with error:" << WSAGetLastError() << std::endl;
			closesocket(controller_2);
			WSACleanup();
			return -1;
		}

		int sendResult = send(controller_2, "Stub2: Begin Reduce..\n", strlen("Stub2: Begin Reduce..\n"), 0);
		std::cout << "Stub2: Reducer Started.." << std::endl;
		if (sendResult != 0) {
			ZeroMemory(stub_2, 256);
			int bytesReceived = recv(controller_2, stub_2, 256, 0);
			printf("%s\n", stub_2);
		}
		closesocket(controller_2);
	}
	closesocket(controller);
	WSACleanup();
	return 0;
}
