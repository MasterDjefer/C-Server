#include "Response.hpp"

Response::Response(SOCKET sock) : mSock(sock), mStatus("200")
{		
}

void Response::setStatus(int status)
{
	mStatus = std::to_string(status);
}

std::string Response::header(ResponseType type)
{
	return "HTTP/1.1 " + mStatus + " Ok\nContent-Type: " + mHeaders[type] + " \n\n";
}

void Response::send(std::string msg, ResponseType type)
{
	msg = header(type) + msg;
	::send(mSock, msg.c_str(), msg.size(), 0);
}

void Response::end(std::string msg)
{
	::send(mSock, msg.c_str(), msg.size(), 0);
}

const std::string Response::mHeaders[] = {"text/html", "text/javascript",  "text/css", "image/jpeg", "image/icon", "image/png"};