#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main() {

	int valread;
	char buffer[256] = { 0 };
	char buffer_2[256] = { 0 };
	// Server Socket Declarations
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;

	if (WSAStartup(wVersion, &wsaData) != 0)
	{
		std::cout << "WSAStartup failed with error: " << std::endl;
		return 1;
	}

	// Creating Server Socket
	SOCKET controller = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (controller == INVALID_SOCKET) {
		std::cout << "Socket function failed with error : " << WSAGetLastError() << std::endl;
		return -1;
	}

	// Binding Server Socket
	sockaddr_in add;
	int len = sizeof(sockaddr_in);
	add.sin_family = AF_INET;
	add.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
	add.sin_port = htons(25000);
	int i = bind(controller, (sockaddr*)&add, len);
	int listenResult = listen(controller, 2);
	if (listenResult != 0) {
		std::cout << "listen error()" << WSAGetLastError() << std::endl;
		return -1;
	}

	// Waiting for connection from client
	// Get client's ip and port
	sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	int caddrelen = sizeof(sockaddr_in);

	SOCKET sclient = accept(controller, (sockaddr*)&caddr, &caddrelen);
	if (sclient == INVALID_SOCKET) {
		return 1;
	}

	// Send notification to stub1 to begin mapping
	std::cout << "Stub1: Mapper Started.." << std::endl;
	send(sclient, "Stub1: Begin Mapping..\n", strlen("Stub1: Begin Mapping..\n"), 0);

	valread = recv(sclient, buffer, 256, 0);
	printf("%s\n", buffer);

	SOCKET sclient_2 = accept(controller, (sockaddr*)&caddr, &caddrelen);
	if (sclient_2 == INVALID_SOCKET) {
		return 1;
	}

	if (valread > 0) {
		std::cout << "Stub2: Reducer Started.." << std::endl;
		send(sclient_2, "Stub2: Begin Reducing..\n", strlen("Stub2: Begin Reducing..\n"), 0);
		valread = recv(sclient_2, buffer_2, 256, 0);
		printf("%s\n", buffer_2);
	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}
