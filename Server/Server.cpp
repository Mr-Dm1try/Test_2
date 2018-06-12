#include "stdafx.h"
#include "Server.h"
using namespace std;

Server::Server() {
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		throw("Не получилось инициализировать Winsock!");
	else cout << "WSAStartup выполнена успешно" << endl;
}

Server::~Server() {
}

void Server::Start(unsigned short port, unsigned short bufSize) {
	servPort = port;
	bufferSize = bufSize;

	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
		throw("Не получилось создать сокет!");
	else cout << "Сокет создан" << endl;

	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(servPort);
	servAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listenSock, (sockaddr*)&servAddr, sizeof(servAddr));
	if (listenSock == INVALID_SOCKET)
		throw("Не получилось привязать сокет!");
	else cout << "Сокет привязан" << endl;

	listen(listenSock, SOMAXCONN);
	if (listenSock == INVALID_SOCKET)
		throw("Не удалось начать прослушивание!");
	else cout << "Начато прослушивание порта " << ntohs(servAddr.sin_port) << endl;
}

void Server::Close() {
	closesocket(listenSock);
	WSACleanup();
	cout << "Сервер остановлен" << endl;
}

void Server::Handle() {
	sockaddr_in clientAddr;
	int clientSize = sizeof(clientAddr);

	SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientSize);
	if (clientSock == INVALID_SOCKET)
		throw("Не получилось создать соединение!");

	char host[NI_MAXHOST];
	char port[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(port, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&clientAddr, sizeof(clientAddr), host, NI_MAXHOST, port, NI_MAXSERV, 0) == 0) {
		cout << host << " подключился к порту " << port << endl;
	}
	else {
		inet_ntop(AF_INET, &clientAddr.sin_addr, host, NI_MAXHOST);
		cout << host << " подключился к порту " << ntohs(clientAddr.sin_port) << endl;
	}

	send(clientSock, "Buffer size: " + bufferSize, bufferSize, 0);

	char *buffer = new char[bufferSize];
	while (true) {
		ZeroMemory(buffer, bufferSize);

		int bytesRecv = recv(clientSock, buffer, bufferSize, 0);
		if (bytesRecv == SOCKET_ERROR) {
			cerr << "Ошибка получения данных! Клиент отсоединен!" << endl;
			break;
		}
		else if (bytesRecv == 0) {
			cout << "Клиент отсоединен!" << endl;
			break;
		}

		cout << buffer;
		send(clientSock, buffer, bytesRecv + 1, 0);
	}

	closesocket(clientSock);
}
