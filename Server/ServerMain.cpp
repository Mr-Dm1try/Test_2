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
		excFlag = true;
		cout << exc << endl;
		exit(1);
	}

	do {
		do {
			cout << "\tВведите номер порта для сервера (>1023 и <65536)" << endl;
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
			cout << exc << endl;
			do {
				cout << "Попробовать еще раз? (1/0)" << endl;
				cin >> excSel;
			} while (excSel != 1 || excSel != 0);
			if (!excSel) exit(1);
		}
	} while (excFlag && excSel);

	cout << "\tВведите количество обработок подключений (<1 для беск.): ";
	cin >> count;

	do
	{
		try {
			myServer->Handle();
		}
		catch (const string exc) {
			cout << exc << endl;
		}
		if (count >= 0) --count;
	} while (count != 0);

	myServer->Close();

	system("pause");
	return 0;
}
