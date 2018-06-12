// ServerMain.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	Server *myServer;
	short excSel;
	bool excFlag = false;
	unsigned short port, bSize;
	short count;
	
	cout << "\tПервоначальная настройка сервера" << endl;

	try {
		myServer = new Server;
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
		do {
			cout << "\tВведите номер порта для сервера (>1023 и <65536): ";
			cin >> port;
		} while (port <= 1023);

		do {
			cout << "\tВведите размер буффера сервера в байтах: ";
			cin >> bSize;
		} while (bSize < 1);
	
		try {
			myServer->Start(port, bSize);
		}
		catch (const string exc) {
			excFlag = true;
			cerr << exc << endl;
			do {
				cout << "Попробовать еще раз? (1/0)" << endl;
				cin >> excSel;
			} while (excSel != 1 && excSel != 0);
			if (!excSel) {
				cout << "Выход..." << endl;
				myServer->Close();
				exit(1);
			}
		}
		catch (...) {
			cerr << "Непредвиденная ошибка! Выход..." << endl;
			exit(1);
		}
	} while (excFlag && excSel);

	cout << "\tВведите количество обработок подключений (<1 для беск.): ";
	cin >> count;

	do {
		try {
			myServer->Handle();
		}
		catch (const string exc) {
			cerr << exc << endl;
		}
		catch (...) {
			cerr << "Непредвиденная ошибка! Выход..." << endl;
			exit(1);
		}

		if (count >= 0) --count;
	} while (count != 0);
 
	myServer->Close();

	system("pause");
	return 0;
}
