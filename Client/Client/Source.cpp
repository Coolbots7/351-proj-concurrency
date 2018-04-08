//Client
#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include "Lane.h"
#include <process.h>

unsigned __stdcall LaneHandler(void* data) {
	Lane lane((int)data);

	lane.Run();

	lane.Close();

	return 0;
}

int main()
{
	for(int i=0;i<4;i++) {
		unsigned ThreadID;
		HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &LaneHandler, (void*) i, 0, &ThreadID);
	}

	WSACleanup();
	system("pause");
	return 0;
}