// Test.cpp: Тестовый клиент без класса.
//

#include "stdafx.h"

//using namespace std;
//
//int main2() {
//	setlocale(LC_ALL, "rus");
//
//	string ipAddr = "127.0.0.1";
//	unsigned short port = 12345;
//
//	WSADATA wsData;
//	WORD ver = MAKEWORD(2, 2);
//	int wsRes = WSAStartup(ver, &wsData);
//	if (wsRes != 0) {
//		cerr << "Не получилось инициализировать winsock! Выход..." << endl;
//		return 1;
//	}
//
//
//	SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
//	if (clientSock == INVALID_SOCKET) {
//		cerr << "Не получилось создать клиентский сокет! Выход..." << endl;
//		return 1;
//	}
//
//
//	sockaddr_in hint;
//	hint.sin_family = AF_INET;
//	hint.sin_port = htons(port);
//	inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);
//
//
//	int connectRes = connect(clientSock, (sockaddr*)&hint, sizeof(hint));
//	if (connectRes == SOCKET_ERROR) {
//		cerr << "Не удалось подключиться к серверу. Выход..." << endl;
//		closesocket(clientSock);
//		WSACleanup();
//		return 1;
//	}
//
//
//	char buffer[1024];
//	string userInp;
//
//	do {
//		cout << ">: ";
//		getline(cin, userInp);
//
//		if (userInp.size() > 0) {
//			int sendMessage = send(clientSock, userInp.c_str(), userInp.size() + 1, 0);
//			if (sendMessage != SOCKET_ERROR) {
//				ZeroMemory(buffer, 1024);
//				int bytesRecv = recv(clientSock, buffer, 1024, 0);
//				if (bytesRecv > 0) {
//					cout << "SERVER: " << buffer << endl;
//				}
//			}
//		}
//	} while (userInp.size() > 0);
//
//
//	system("pause");
//    return 0;
//}

