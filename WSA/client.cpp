#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <afunix.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT     ("8888")
#define BUFF_LEN (512)

int main() {
	WSADATA wsaData;
	struct addrinfo *result, hints;
	SOCKET ConnectSocket;
	const char* sendbuf = "this is a test";
	char recvbuf[BUFF_LEN];
	int tmp;
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	getaddrinfo("127.0.0.1", PORT, &hints, &result);
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result);

	tmp = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	printf("Bytes Sent: %ld\n", tmp);

	shutdown(ConnectSocket, SD_SEND);

	tmp = recv(ConnectSocket, recvbuf, BUFF_LEN, 0);
	printf("Bytes received: %d\n", tmp);

	return 0;
}