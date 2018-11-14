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
void RequestParser::parse()
{
	findMethod();
	findUrl();

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
		for (std::map<std::string, std::string>::iterator it = mParams.begin(); it != mParams.end(); ++it)
		{
			newUrl += "/:" + it->first;
		}			
		
		//new url with ,,:,,
		memset(mUrl, 0, 100);
		memcpy(mUrl, newUrl.c_str(), newUrl.size());
	}	
	if (strlen(mUrl) != 1 && mUrl[strlen(mUrl) - 1] == '/')
	{
		mUrl[strlen(mUrl) - 1] = 0;
	}
}
void RequestParser::setZero()
{
	memset(mRequest, 0, 1000);
	memset(mMethod, 0, 10);
	memset(mUrl, 0, 100);
}
void RequestParser::setRequest(char *request)
{
	setZero();
	memcpy(mRequest, request, strlen(request));
	parse();		
}	
Request RequestParser::request() const
{
	return Request(std::string(mMethod), std::string(mUrl), mParams);
}	

