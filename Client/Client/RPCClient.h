#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

struct ClientMessage {
	byte Action;
	byte Quadrant;
};

class RPCClient {
private:
	SOCKET Connection;

	int Send(ClientMessage message) {
		char *data = new char[sizeof(ClientMessage)];
		memcpy(data, &message, sizeof(data));

		return send(Connection, data, sizeof(data), 0);
	}

public:
	RPCClient(int ID) {
		WSAData wsaData;
		WORD DllVersion = MAKEWORD(2, 1);
		if (WSAStartup(DllVersion, &wsaData) != 0)
		{
			MessageBoxA(NULL, ID + ": Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}

		SOCKADDR_IN addr;
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;

		Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
		{
			MessageBoxA(NULL, ID + ": Failed to Connect", "Error", MB_OK | MB_ICONERROR);
			exit(1);
		}
	}

	void Close() {		
		printf("Closing socket to server: %d\n", Connection);
		closesocket(Connection);
	}

	bool LockQuadrant(int Quadrant) {
		ClientMessage message;
		message.Action = 0;
		message.Quadrant = Quadrant;

		if(Send(message) == SOCKET_ERROR) {
			printf("send() failed with error code: %d\n", WSAGetLastError());
			return false;
		}
		else {
			//wait for lock response
			char response[1];
			recv(Connection, response, sizeof(response), 0);
		}

		return true;
	}

	bool UnlockQuadrant(int Quadrant) {
		ClientMessage message;
		message.Action = 1;
		message.Quadrant = Quadrant;

		if(Send(message) == SOCKET_ERROR) {
			printf("send() failed with error code: %d\n", WSAGetLastError());
			return false;
		}

		return true;
	}
};