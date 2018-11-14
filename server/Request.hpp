#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <map>

class Request
{
	std::string mMethod;
	std::string mUrl;
	std::map<std::string, std::string> mParams;
	
public:
	Request(std::string method, std::string url, std::map<std::string, std::string> params);
	std::string method() const;
	std::string url() const;
	std::string params(std::string key);
};
#endif