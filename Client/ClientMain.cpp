// ClientMain.cpp: ���������� ����� ����� ��� ����������� ����������.
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


	cout << "\t�������������� ��������� �������" << endl;
	try {
		myClient = new Client;
	}
	catch (const string exc) {
		cerr << exc << " �����..." << endl;
		exit(1);
	}
	catch (...) {
		cerr << "�������������� ������! �����..." << endl;
		exit(1);
	}
	
	do {
		excFlag = false;
		cout << "\t������� IP-����� �������: ";
		cin >> ipAddr;
		do {
			cout << "\t������� ���� �������: ";
			cin >> port;
		} while (port <= 1023);
		do {
			cout << "\t������� ������ ������ �������: ";
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
			cerr << "�������������� ������!" << endl;
		}
		myClient->Disconnect();

		do {
			cout << "\t������������ ��� ���? (1/0)" << endl << "\t";
			cin >> sel;
		} while (sel != 1 && sel != 0);

		if (!sel && excFlag) {
			cout << "\t�����..." << endl;
			break;
		}
	} while (sel);

	myClient->Close();

	system("pause");
    return 0;
}