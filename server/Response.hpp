#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include <winsock2.h>
 
class Response
{	
	std::string mHeaders[3];
	SOCKET mSock;
	std::string mStatus;
public:
	enum TextType
	{
		html,
		js, 
		css
	};

	Response(SOCKET sock);
	void setStatus(int status);
	void send(std::string msg, TextType type);
	void end(std::string msg);
private:
	std::string header(TextType type);
};
#endif