// Test.cpp: предыдущая тестовая версия программы без использования класса
//

#include "stdafx.h"

//using namespace std;
//
//int main2() {
//	setlocale(LC_ALL, "rus");
//
//	WSADATA wsData;
//	WORD ver = MAKEWORD(2, 2);
//
//	int wsOk = WSAStartup(ver, &wsData);
//	if (wsOk != 0) {
//		cerr << "Не получилось инициализировать winsock! Выход..." << endl;
//		return 1;
//	}
//
//
//	SOCKET listeningSock = socket(AF_INET, SOCK_STREAM, 0);
//	if (listeningSock == INVALID_SOCKET) {
//		cerr << "Не получилось создать слушающий сокет! Выход..." << endl;
//		return 1;
//	}
//
//
//	sockaddr_in hint;
//	hint.sin_family = AF_INET;
//	hint.sin_port = htons(12345);
//	hint.sin_addr.S_un.S_addr = INADDR_ANY;
//
//	bind(listeningSock, (sockaddr*)&hint, sizeof(hint));
//
//
//	listen(listeningSock, SOMAXCONN);
//
//
//	sockaddr_in client;
//	int clientSize = sizeof(client);
//
//	SOCKET clientSock = accept(listeningSock, (sockaddr*)&client, &clientSize);
//	if (clientSock == INVALID_SOCKET) {
//		cerr << "Не получилось создать соединение! Выход..." << endl;
//		return 1;
//	}
//
//
//	char host[NI_MAXHOST];
//	char port[NI_MAXSERV];
//
//	ZeroMemory(host, NI_MAXHOST);
//	ZeroMemory(port, NI_MAXSERV);
//
//	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, port, NI_MAXSERV, 0) == 0) {
//		cout << host << " подключился к порту " << port << endl;
//	}
//	else {
//		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
//		cout << host << " подключился к порту " << ntohs(client.sin_port) << endl;
//	}
//
//
//	closesocket(listeningSock);
//
//
//	char buffer[1024];
//	while (true) {
//		ZeroMemory(buffer, 1024);
//
//		int bytesRecv = recv(clientSock, buffer, 1024, 0);
//		if (bytesRecv == SOCKET_ERROR) {
//			cerr << "Ошибка получения данных. Выход..." << endl;
//			break;
//		}
//		else if (bytesRecv == 0) {
//			cout << "Клиент отсоединен..." << endl;
//			break;
//		}
//
//		cout << buffer;
//		send(clientSock, buffer, bytesRecv + 1, 0);
//	}
//
//	closesocket(clientSock);
//
//	WSACleanup();
//
//	system("pause");
//    return 0;
//}

