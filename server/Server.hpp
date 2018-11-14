#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <winsock2.h>
#include "Request.hpp"
#include "Response.hpp"
#include "RequestParser.hpp"


typedef std::function<void()> Func;
//typedef void(*Func)();
//typedef void(*RequestCallback)(Request, Response);

typedef std::function<void(Request, Response)> RequestCallback;

class Server
{
	SOCKET sock;
	sockaddr_in sockAddr;
	const int bufSize = 1000;
	char buf[1000];
	std::map<std::string, RequestCallback> mRequestsMap;

public:
	Server();
	void listen(int port, Func f);
	void get(std::string url, RequestCallback callback);
private:
	void setZero();
	
	void acceptConnection();
};
#endif