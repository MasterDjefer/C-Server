#include "Response.hpp"

Response::Response(SOCKET sock) : mSock(sock)
{		
	mHead = "HTTP/1.1 200 Ok\nContent-Type: text/html; charset=UTF-8\n\n";
}

void Response::send(std::string msg)
{
	msg = mHead + msg;
	::send(mSock, msg.c_str(), msg.size(), 0);
}
void Response::end(std::string msg)
{
	::send(mSock, msg.c_str(), msg.size(), 0);
}
