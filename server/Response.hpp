#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <winsock2.h>
 
class Response
{	
	static const std::string mHeaders[];
	SOCKET mSock;
	std::string mStatus;
public:
	enum ResponseType
	{
		html,
		js, 
		css,
		jpg,
		ico, 
		png
	};

	Response(SOCKET sock);
	void setStatus(int status);
	void send(std::string msg, ResponseType type);
	void end(std::string msg);
private:
	std::string header(ResponseType type);
};
#endif