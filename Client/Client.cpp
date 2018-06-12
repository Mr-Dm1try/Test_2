#include "stdafx.h"
#include "Client.h"


Client::Client() {
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
		throw("Не получилось инициализировать Winsock!");
	else cout << "WSAStartup выполнена успешно" << endl;
}

Client::~Client() {
}

void Client::Connect(string addr, unsigned short port, unsigned short bufSize) {
	ipAddr = addr;
	servPort = port;
	bufferSize = bufSize;
	string clearBuf;


	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET)
		throw("Не получилось создать клиентский сокет!");
	else cout << "Клиентский сокет создан успешно" << endl;

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(servPort);
	inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);


	int connectRes = connect(clientSock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == SOCKET_ERROR) 
		throw("Не удалось подключиться к серверу.");
	else cout << "Соединение успешно установлено" << endl;


	char *buffer = new char[bufferSize];
	string userInp;

	getline(cin, clearBuf);
	do {
		cout << "INPUT: ";
		getline(cin, userInp);

		if (userInp.size() > 0) {
			int sendMessage = send(clientSock, userInp.c_str(), userInp.size() + 1, 0);
			if (sendMessage != SOCKET_ERROR) {
				ZeroMemory(buffer, bufferSize);
				int bytesRecv = recv(clientSock, buffer, bufferSize, 0);
				if (bytesRecv > 0) {
					cout << "SERVER: " << string(buffer, 0, bytesRecv)<< endl;
				}
			}
		}

		if (userInp == "File") {
			FileTransfer();
			getline(cin, clearBuf);
		}
	} while (userInp.size() > 0);

	cout << "Подключение прервано!" << endl;
}

void Client::FileTransfer() {
	char *buffer = new char[bufferSize];
	string userInp;
	ifstream fin;

	cout << "FILE NAME: ";
	cin >> userInp;

	if (userInp.size() > 0) {
		try {
			fin.open(userInp);
		}
		catch (...){
			cerr << "Ошибка при открытии файла!" << endl;
			return;
		}

		int sendMessage = send(clientSock, userInp.c_str(), userInp.size() + 1, 0);
		if (sendMessage != SOCKET_ERROR) {
			while (!fin.eof()) {
				ZeroMemory(buffer, bufferSize);
				fin.read(buffer, bufferSize);

				sendMessage = send(clientSock, buffer, bufferSize, 0);
			}

			fin.close();

			int bytesRecv = recv(clientSock, buffer, bufferSize, 0);
			if (bytesRecv > 0) {
				cout << "SERVER: " << string(buffer, 0, bytesRecv) << endl;
			}
		}
	}

}

void Client::Disconnect(){
	closesocket(clientSock);
}

void Client::Close() {
	WSACleanup();
}