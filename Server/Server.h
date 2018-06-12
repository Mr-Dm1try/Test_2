#pragma once
class Server {
private:
	SOCKET listenSock;
	WSADATA wsData;
	unsigned short servPort, bufferSize;

public:
	Server();
	~Server();
	void Start(unsigned short port, unsigned short bufSize);
	void Close();
	void Handle();
};


