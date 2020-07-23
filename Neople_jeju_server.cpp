#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <ctime>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int Main(void)
{
	WSADATA     wsaData;
	SOCKET      listenSocket;
	SOCKADDR_IN servAddr;

	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed socket()" << "\n";
		return 1;
	}

	
	listenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		WSACleanup();
		cout << "Failed socket()" << endl;
		return 1;
	}

	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	
	servAddr.sin_port = htons(30002);
	if (bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		cout << "Binding Error" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		cout << "listen Error" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}



	SOCKADDR_IN  clientAddr;
	SOCKET       clientSocket;
	int          sizeClientAddr = sizeof(clientAddr);
	char sendData[255] = "Go! Jeju island!";
	char recvByte;
	char recvData[255];
	int recvCount = 0;


	
	clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &sizeClientAddr);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Failed accept()" << endl;
		recvCount = 0;

		cout << "accept client socket : " << clientSocket << endl;
		
		send(clientSocket, sendData, strlen(sendData) + 1, 0);

		
		cout << "recv count : ";
		while ((recvByte = recv(clientSocket, recvData, sizeof(recvData), 0)) > 0)
		{
			
			cout << ++recvCount << endl;
			send(clientSocket, recvData, recvByte, 0);
		}

		cout << endl;
		closesocket(clientSocket);
		cout << "close socket : " << clientSocket << endl;


	}


	closesocket(clientSocket);

	closesocket(listenSocket);
	WSACleanup();

	system("pause");

	return 0;
}


