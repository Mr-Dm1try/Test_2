#pragma once
using namespace std;

class Client {
private:
	SOCKET clientSock;
	WSAData wsData;
	string ipAddr;
	unsigned short servPort, bufferSize;

public:
	Client();
	void Connect(string addr, unsigned short port, unsigned short bufSize);
	void FileTransfer();
	void Disconnect();
	void Close();
	~Client();
};

