#include "Response.hpp"

Response::Response(SOCKET sock) : mSock(sock), mStatus("200")
{		
	mHeaders[0] = "text/html;";
	mHeaders[1] = "text/javascript;";
	mHeaders[2] = "text/css;";
}

void Response::setStatus(const std::string &status)
{
	mStatus = status;
}

std::string Response::header(TextType type)
{
	return "HTTP/1.1 " + mStatus + " Ok\nContent-Type: " + mHeaders[type] + " charset=UTF-8\n\n";
}

void Response::send(std::string msg, TextType type)
{
	msg = header(type) + msg;
	::send(mSock, msg.c_str(), msg.size(), 0);
}

void Response::end(std::string msg)
{
	msg = "HTTP/1.1 200 Ok\nContent-Type: image/ico charset=UTF-8\n\n" + msg;
	::send(mSock, msg.c_str(), msg.size(), 0);
}
