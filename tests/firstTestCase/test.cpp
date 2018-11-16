#include <iostream>
#include <winsock2.h>
#include "Test.hpp"

int main() 
{		
	Test::note("initialize win sockets");
	WSADATA wsaData = {0};
	int iResult = iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{		
		Test::note("WSAStartup failed");
		return 1;
	}

	Test::note("create socket");
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
	{		
		Test::note("sock create error");
		return 1;
	}

	Test::note("create struct for connect");
	struct sockaddr_in sockAddr = {0};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sockAddr.sin_port = htons(12345);

	iResult = connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if (iResult != 0) 
	{		
		Test::note("connect error");
		return 1;
	}
	Test::note("connected");

	char buf[100]; 
	const int n = 100;
	memset(buf, 0, n);
	
	const char *request = "GET / ";
	send(sock, request, strlen(request), 0);
	recv(sock, buf, n, 0);
	Test::verify("verify received data(GET /)", Test::CompareData<std::string>(std::string(buf), "Main page"));
	std::cout << request << "|" << buf << "|"<< std::endl;
	memset(buf, 0, n);
	

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	request = "GET /test?variable=zero ";
	send(sock, request, strlen(request), 0);
	recv(sock, buf, n, 0);
	Test::verify("verify received data(GET /test/:variable)", Test::CompareData<std::string>(std::string(buf), "zero is shit"));
	std::cout << request << "|" << buf << "|"<< std::endl;
	memset(buf, 0, n);
	
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	request = "GET /?name=john&age=13 ";
	send(sock, request, strlen(request), 0);
	recv(sock, buf, n, 0);
	Test::verify("verify received data(GET /:name/:age)", Test::CompareData<std::string>(std::string(buf), "john is 13"));
	std::cout << request << "|" << buf << "|"<< std::endl;
	memset(buf, 0, n);	

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	request = "POST /me \nname=cat&age=evil";
	send(sock, request, strlen(request), 0);
	recv(sock, buf, n, 0);
	Test::verify("verify received data(POST /me)", Test::CompareData<std::string>(std::string(buf), "cat is evil"));
	std::cout << request << "|" << buf << "|"<< std::endl;
	memset(buf, 0, n);

	//exit
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	request = "EXIT";
	send(sock, request, strlen(request), 0);

	system("pause");
}