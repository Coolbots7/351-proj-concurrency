#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <process.h>

unsigned __stdcall ClientHandler(void *data) {
	SOCKET ClientSocket = (SOCKET)data;

	while(true) {

		char receiveBuffer[1];
		int recv_len = recv(ClientSocket, receiveBuffer, 1, 0);
		if (recv_len == 0)
		{
			printf("Client %d disconnected\n", ClientSocket);
			break;
		}
		else if(recv_len == SOCKET_ERROR)
		{
			printf("Socket descriptor, after recv(): %d\n", ClientSocket);
			printf("recv() failed with error code: %d\n", WSAGetLastError());
			break;
		}

		printf("Received char %d from client %d\n", receiveBuffer[0], ClientSocket);

	}

	printf("Closing socket to client: %d\n", ClientSocket);
	closesocket(ClientSocket);
	return 0;
}

int main()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	std::cout << "SERVER STARTED\n\n";

	SOCKET newConnection;
	while((newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen)))
	{
		std::cout << "\nNew Client!...";

		//Start new thread
		unsigned ThreadID;
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &ClientHandler, (void*)newConnection, 0, &ThreadID);

		printf("Started thread %d for client %d\n", ThreadID, newConnection);
	}

	system("pause");
	return 0;
}