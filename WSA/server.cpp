#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <afunix.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT ("8888")
#define BUFF_LEN (512)

int maina()
{
	WSADATA wsaData;
	SOCKET ListenSocket, ClientSocket;
	char recvbuf[BUFF_LEN];
	int send_num, recv_num;
	struct addrinfo* result = NULL, hints;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &result);

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result);

	printf("listen on port %s ...\n", PORT);
	listen(ListenSocket, SOMAXCONN);

	ClientSocket = accept(ListenSocket, NULL, NULL);

	recv_num = recv(ClientSocket, recvbuf, BUFF_LEN, 0);
	printf("Bytes received: %d\n", recv_num);
	send_num = send(ClientSocket, recvbuf, recv_num, 0);
	printf("Bytes sent: %d\n", send_num);

	shutdown(ClientSocket, SD_BOTH);
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}