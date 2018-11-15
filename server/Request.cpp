#include "Request.hpp"

Request::Request(std::string method, std::string url, std::unordered_map<std::string, std::string> params, std::unordered_map<std::string, std::string> body) : 
	mMethod(method), mUrl(url), mParams(params), mBody(body)
{		
}

std::string Request::method() const
{
	return mMethod;
}
std::string Request::url() const
{
	return mUrl;
}
std::string Request::params(std::string key)
{
	if (mParams.find(key) == mParams.end())
		throw "invalid params";
	return mParams[key];
}
std::string Request::body(std::string key)
{
	if (mBody.find(key) == mBody.end())
		throw "invalid key in body";
	return mBody[key];
}