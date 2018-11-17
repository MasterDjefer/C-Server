#include "RequestParser.hpp"

void RequestParser::findMethod()
{		
	int i = 0;
	while (mRequest[i] != ' ')
	{
		mMethod[i] = mRequest[i];
		i++;
	}
}
void RequestParser::findUrl()
{		
	int j = 0;
	int i = strlen(mMethod) + 1;
	while (mRequest[i] != ' ')
	{
		mUrl[j++] = mRequest[i++];
	}
}	
void RequestParser::parseHead()
{
	findMethod();
	findUrl();
}
void RequestParser::parseGet()
{
	//  /?inputField=...&inputField2=...		=>
	//  /:val1/:val2	
	
	std::string cUrl = std::string(mUrl);
	std::string newUrl = "";
	int markIndex = cUrl.find("?");
	if (markIndex != std::string::npos)
	{
		int lastVariable = 0;//parse last variable, later will equal 1
		newUrl = cUrl.substr(0, markIndex);
		cUrl = cUrl.substr(markIndex + 1, cUrl.size() - markIndex + 1);
		
		while (true)
		{							
			int markEqual = cUrl.find("=");
			if (markEqual == std::string::npos)
			{
				break;
			}
			
			std::string variableName = cUrl.substr(0, markEqual);
			
			int markAmp = cUrl.find("&");
			if (markAmp == std::string::npos)
			{
				markAmp = cUrl.size() - 1;
				lastVariable = 1;
			}
				
			std::string variableValue = cUrl.substr(markEqual + 1, markAmp - markEqual - 1 + lastVariable);
			
			//change url!
			cUrl = cUrl.substr(markAmp + 1, cUrl.size() - markAmp);
			
			mParams.insert(std::pair<std::string, std::string>(variableName, variableValue));
		}
		if (newUrl.at(newUrl.size() - 1) == '/')
		{
			newUrl = newUrl.substr(0, newUrl.size() - 1);
		}
		std::string tempUrl = "";
		for (std::unordered_map<std::string, std::string>::iterator it = mParams.begin(); it != mParams.end(); ++it)
		{
			tempUrl = "/:" + it->first + tempUrl;
		}	
		newUrl += tempUrl;		
		
		//new url with ,,:,,
		memset(mUrl, 0, 100);
		memcpy(mUrl, newUrl.c_str(), newUrl.size());
	}	
	if (strlen(mUrl) != 1 && mUrl[strlen(mUrl) - 1] == '/')
	{
		mUrl[strlen(mUrl) - 1] = 0;
	}
}
void RequestParser::parsePost()
{
	//  name=pasha&age=16		=>
	//  map.push("name", "pasha"), map.push("age", "16") 	

	int i = strlen(mRequest);
	while (mRequest[--i] != '\n');
	char *temp = mRequest;
	temp += i + 1;

	std::string body(temp);
	int lastVariable = 0;//parse last variable, later will be equal 1
	while (true)
	{							
		int markEqual = body.find("=");
		if (markEqual == std::string::npos)
		{
			break;
		}
		
		std::string variableName = body.substr(0, markEqual);
		
		int markAmp = body.find("&");
		if (markAmp == std::string::npos)
		{
			markAmp = body.size() - 1;
			lastVariable = 1;
		}
			
		std::string variableValue = body.substr(markEqual + 1, markAmp - markEqual - 1 + lastVariable);
		
		//change url!
		body = body.substr(markAmp + 1, body.size() - markAmp);
		
		mBody.insert(std::pair<std::string, std::string>(variableName, variableValue));
	}
}
void RequestParser::setZero()
{
	memset(mRequest, 0, 10000);
	memset(mMethod, 0, 10);
	memset(mUrl, 0, 1000);
}
void RequestParser::setRequest(char *request)
{
	setZero();
	memcpy(mRequest, request, strlen(request));
	parseHead();	

	if (!strcmp(mMethod, "GET"))
	{
		parseGet();
	}
	else
	if (!strcmp(mMethod, "POST"))
	{
		parsePost();
	}
}	
Request RequestParser::request() const
{
	return Request(std::string(mMethod), std::string(mUrl), mParams, mBody);
}	

