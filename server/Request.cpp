#include "Request.hpp"

Request::Request(std::string method, std::string url, std::map<std::string, std::string> params) : mMethod(method), mUrl(url), mParams(params)
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