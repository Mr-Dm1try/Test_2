// ServerMain.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	
	cout << "\t�������������� ��������� �������" << endl;

	try {
		myServer = new Server;
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
		do {
			cout << "\t������� ����� ����� ��� ������� (>1023 � <65536): ";
			cin >> port;
		} while (port <= 1023);

		do {
			cout << "\t������� ������ ������� ������� � ������: ";
			cin >> bSize;
		} while (bSize < 1);
	
		try {
			myServer->Start(port, bSize);
		}
		catch (const string exc) {
			excFlag = true;
			cerr << exc << endl;
			do {
				cout << "����������� ��� ���? (1/0)" << endl;
				cin >> excSel;
			} while (excSel != 1 && excSel != 0);
			if (!excSel) {
				cout << "�����..." << endl;
				myServer->Close();
				exit(1);
			}
		}
		catch (...) {
			cerr << "�������������� ������! �����..." << endl;
			exit(1);
		}
	} while (excFlag && excSel);

	cout << "\t������� ���������� ��������� ����������� (<1 ��� ����.): ";
	cin >> count;

	do {
		try {
			myServer->Handle();
		}
		catch (const string exc) {
			cerr << exc << endl;
		}
		catch (...) {
			cerr << "�������������� ������! �����..." << endl;
			exit(1);
		}

		if (count >= 0) --count;
	} while (count != 0);
 
	myServer->Close();

	system("pause");
	return 0;
}
