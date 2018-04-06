//Client
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

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
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	else
	{
		std::cout << "Connected to server!\n" << std::endl;

		for(int i=0;i<10;i++) {

			printf("Sending char: %d\n", i);

			char sendBuf[1];
			sendBuf[0] = i;

			if(send(Connection, sendBuf, 1, 0) == SOCKET_ERROR) {
				printf("send() failed with error code: %d\n", WSAGetLastError());
			}
		}

	}

	printf("Closing socket to server: %d\n", Connection);

	closesocket(Connection);
	WSACleanup();

	system("pause");

	return 0;
}