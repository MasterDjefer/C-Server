#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H
#include <string>
#include <map>
#include <cstring>
#include "Request.hpp"

class RequestParser
{
	char mRequest[1000];
	char mMethod[10];
	char mUrl[100];
	std::map<std::string, std::string> mParams;
	
	void findMethod();
	void findUrl();
	void parse();
	void setZero();
	
public:
	void setRequest(char *request);	
	Request request() const;
};
#endif