#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <string>
#include <unordered_map>
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
	const int bufSize = 100000;
	char buf[100000];
	std::unordered_map<std::string, RequestCallback> mGetRequestsMap;
	std::unordered_map<std::string, RequestCallback> mPostRequestsMap;

public:
	Server();
	~Server();
	void listen(int port, Func f);
	void get(std::string url, RequestCallback callback);
	void post(std::string url, RequestCallback callback);
private:
	void setZero();	
	void acceptConnection();
	void defunctRequest(Request req, Response res);
};
#endif