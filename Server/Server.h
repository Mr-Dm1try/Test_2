#pragma once
class Server {
private:
	SOCKET listenSock, clientSock;
	WSADATA wsData;
	unsigned short servPort, bufferSize;

public:
	Server();
	~Server();
	void Start(unsigned short port, unsigned short bufSize);
	void Handle();
	void FileReceive();
	void Close();
};


