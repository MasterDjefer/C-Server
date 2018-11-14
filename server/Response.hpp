#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <winsock2.h>

class Response
{
	SOCKET mSock;
	std::string mPage;
	std::string mText;
	std::string mHead;
public:
	Response(SOCKET sock);
	void send(std::string msg);
	void end(std::string msg);
};
#endif