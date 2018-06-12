#include "stdafx.h"
#include "Server.h"
using namespace std;

Server::Server() {
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		throw("�� ���������� ���������������� Winsock!");
	else cout << "WSAStartup ��������� �������" << endl;
}

Server::~Server() {
}

void Server::Start(unsigned short port, unsigned short bufSize) {
	servPort = port;
	bufferSize = bufSize;

	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
		throw("�� ���������� ������� �����!");
	else cout << "����� ������" << endl;

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(servPort);
	servAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listenSock, (sockaddr*)&servAddr, sizeof(servAddr));
	if (listenSock == INVALID_SOCKET)
		throw("�� ���������� ��������� �����!");
	else cout << "����� ��������" << endl;

	listen(listenSock, SOMAXCONN);
	if (listenSock == INVALID_SOCKET)
		throw("�� ������� ������ �������������!");
	else cout << "������ ������������� ����� " << ntohs(servAddr.sin_port) << endl;
}

void Server::Close() {
	closesocket(listenSock);
	WSACleanup();
	cout << "������ ����������" << endl;
}

void Server::Handle() {
	sockaddr_in clientAddr;
	int clientSize = sizeof(clientAddr);

	SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientSize);
	if (clientSock == INVALID_SOCKET)
		throw("�� ���������� ������� ����������!");

	char host[NI_MAXHOST];
	char port[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(port, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&clientAddr, sizeof(clientAddr), host, NI_MAXHOST, port, NI_MAXSERV, 0) == 0) {
		cout << host << " ����������� � ����� " << port << endl;
	}
	else {
		inet_ntop(AF_INET, &clientAddr.sin_addr, host, NI_MAXHOST);
		cout << host << " ����������� � ����� " << ntohs(clientAddr.sin_port) << endl;
	}

	send(clientSock, "Buffer size: " + bufferSize, bufferSize, 0);

	char *buffer = new char[bufferSize];
	while (true) {
		ZeroMemory(buffer, bufferSize);

		int bytesRecv = recv(clientSock, buffer, bufferSize, 0);
		if (bytesRecv == SOCKET_ERROR) {
			cerr << "������ ��������� ������! ������ ����������!" << endl;
			break;
		}
		else if (bytesRecv == 0) {
			cout << "������ ����������!" << endl;
			break;
		}

		cout << buffer;
		send(clientSock, buffer, bytesRecv + 1, 0);
	}

	closesocket(clientSock);
}
