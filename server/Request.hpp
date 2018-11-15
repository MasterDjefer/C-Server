#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <unordered_map>

class Request
{
	std::string mMethod;
	std::string mUrl;
	std::unordered_map<std::string, std::string> mParams;
	std::unordered_map<std::string, std::string> mBody;
	
public:
	Request(std::string method, std::string url, std::unordered_map<std::string, std::string> params, std::unordered_map<std::string, std::string> body);
	std::string method() const;
	std::string url() const;
	std::string params(std::string key);
	std::string body(std::string key);
};
#endif