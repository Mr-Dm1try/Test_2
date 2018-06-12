// ClientMain.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	Client *myClient;
	short sel;
	bool excFlag = false;
	string ipAddr;
	unsigned short port, bSize;


	cout << "\tПервоначальная настройка клиента" << endl;
	try {
		myClient = new Client;
	}
	catch (const string exc) {
		cerr << exc << " Выход..." << endl;
		exit(1);
	}
	catch (...) {
		cerr << "Непредвиденная ошибка! Выход..." << endl;
		exit(1);
	}
	
	do {
		excFlag = false;
		cout << "\tВведите IP-адрес сервера: ";
		cin >> ipAddr;
		do {
			cout << "\tВведите порт сервера: ";
			cin >> port;
		} while (port <= 1023);
		do {
			cout << "\tВведите размер буфера клиента: ";
			cin >> bSize;
		} while (bSize < 1);

		try {
			myClient->Connect(ipAddr, port, bSize);
		}
		catch (const string exc) {
			excFlag = true;
			cerr << exc << endl;
		}
		catch (...) {
			excFlag = true;
			cerr << "Непредвиденная ошибка!" << endl;
		}
		myClient->Disconnect();

		do {
			cout << "\tПодключиться еще раз? (1/0)" << endl << "\t";
			cin >> sel;
		} while (sel != 1 && sel != 0);

		if (!sel && excFlag) {
			cout << "\tВыход..." << endl;
			break;
		}
	} while (sel);

	myClient->Close();

	system("pause");
    return 0;
}