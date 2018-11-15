#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <cstring>
#include "Request.hpp"
 
class RequestParser
{
	char mRequest[1000];
	char mMethod[10];
	char mUrl[100];
	std::unordered_map<std::string, std::string> mParams;
	std::unordered_map<std::string, std::string> mBody;
	
	void findMethod();
	void findUrl();
	void parseHead();
	void parseGet();
	void parsePost();
	void setZero();
	
public:
	void setRequest(char *request);	
	Request request() const;
};
#endif