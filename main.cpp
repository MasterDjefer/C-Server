#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <map>
//#include <thread>
#include <conio.h>
#include <winsock2.h>
using namespace std;

class Request;
class Response;

typedef void(*Func)();
typedef void(*RequestCallback)(Request, Response);

class Request
{
	string mMethod;
	string mUrl;
	map<string, string> mParams;
	
public:
	Request(string method, string url, map<string, string> params) : mMethod(method), mUrl(url), mParams(params)
	{		
	}

	string method() const
	{
		return mMethod;
	}
	string url() const
	{
		return mUrl;
	}
	map<string, string> params() const
	{
		return mParams;
	}
};
class Response
{
	SOCKET mSock;
	string mPage;
	string mText;
	string mHead;
public:
	Response(SOCKET sock) : mSock(sock)
	{		
		mHead = "HTTP/1.1 200 Ok\nContent-Type: text/html; charset=UTF-8\n\n";
	}

	void send(string msg)
	{
		resetPage(msg);
		::send(mSock, mPage.c_str(), mPage.size(), 0);
	}
	void end(string msg)
	{
		msg = mHead  + msg;

		::send(mSock, msg.c_str(), msg.size(), 0);
	}
private:
	void resetPage(string msg)
	{
		mPage = 
			"HTTP/1.1 200 Ok\n" 
			"Content-Type: text/html; charset=UTF-8\n\n" 
			"<!DOCTYPE>" 
			"<html>" 
				"<head>" 
					"<title>Web C</title>" 
					"<style> body { background-color: #A9D0F5 }</style>" 
				"</head>" 
				"<body>" 
					"<h1>" + msg + "</h1>" 
					"<form id='form' action='http://localhost:12345'>"
						"<input type='text' name='inputField'> <br>"
						"<input type='text' name='inputField2'> <br>"
						"<input type='submit' value='send data'>"
					"</form>"
					
					"<input id='button' type='button' value='Press me!'>"
					
					"<script type='text/javascript' src='script.js'></script>"
				"</body>" 
			"</html>";
	}
};

class RequestParser
{
	char mRequest[1000];
	char mMethod[10];
	char mUrl[100];
	map<string, string> mParams;
	
	void findMethod()
	{		
		int i = 0;
		while (mRequest[i] != ' ')
		{
			mMethod[i] = mRequest[i];
			i++;
		}
	}
	void findUrl()
	{		
		int j = 0;
		int i = strlen(mMethod) + 1;
		while (mRequest[i] != ' ')
		{
			mUrl[j++] = mRequest[i++];
		}
	}	
	void parse()
	{
		findMethod();
		findUrl();

		//  /?inputField=...&inputField2=...		=>
		//  /:val1/:val2
		
		
		string cUrl = string(mUrl);
		string newUrl = "";
		int markIndex = cUrl.find("?");
		if (markIndex != string::npos)
		{
			int lastVariable = 0;//parse last variable, later will equal 1
			newUrl = cUrl.substr(0, markIndex);
			cUrl = cUrl.substr(markIndex + 1, cUrl.size() - markIndex + 1);
			
			while (true)
			{							
				int markEqual = cUrl.find("=");
				if (markEqual == string::npos)
				{
					break;
				}
				
				string variableName = cUrl.substr(0, markEqual);
				
				int markAmp = cUrl.find("&");
				if (markAmp == string::npos)
				{
					markAmp = cUrl.size() - 1;
					lastVariable = 1;
				}
					
				string variableValue = cUrl.substr(markEqual + 1, markAmp - markEqual - 1 + lastVariable);
				
				//change url!
				cUrl = cUrl.substr(markAmp + 1, cUrl.size() - markAmp);
				
				mParams.insert(pair<string, string>(variableName, variableValue));
			}
			if (newUrl.at(newUrl.size() - 1) == '/')
			{
				newUrl = newUrl.substr(0, newUrl.size() - 1);
			}
			for (map<string, string>::iterator it = mParams.begin(); it != mParams.end(); ++it)
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
	void setZero()
	{
		memset(mRequest, 0, 1000);
		memset(mMethod, 0, 10);
		memset(mUrl, 0, 100);
	}
	
public:
	void setRequest(char *request)
	{
		setZero();
		memcpy(mRequest, request, strlen(request));
		parse();		
	}
	
	Request request() const
	{
		return Request(string(mMethod), string(mUrl), mParams);
	}	
};


class Server
{
	SOCKET sock;
	sockaddr_in sockAddr;
	const int bufSize = 1000;
	char buf[1000];
	map<string, RequestCallback> mRequestsMap;

public:
	Server()
	{
		WSADATA wsaData = {0};
		int iResult = iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) 		
			throw "WSAStartup failed";		

		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock < 0)
			throw "sock create error";  
		setZero();
	}
	void listen(int port, Func f = NULL)
	{
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		sockAddr.sin_port = htons(port);

		int res = bind(sock, (sockaddr*)&sockAddr, sizeof(sockAddr));
		if (res < 0)
			throw "bind error"; 

		res = ::listen(sock, 10);
		if (res < 0)
			throw "listen error";  

		get("/mySecretRequest", [](Request req, Response res)
		{
			res.send("can\'t get " + req.url());
		});

		if (f)
		{
			f();
		}
		acceptConnection();
	}
	void get(string url, RequestCallback callback)
	{
		mRequestsMap.insert(std::pair<string, RequestCallback>(url, callback));
	}
private:
	void setZero()
	{
		memset(buf, 0, bufSize);
	}
	
	void acceptConnection()
	{
		SOCKET temp;
		while (true)
		{
			temp = accept(sock, NULL, NULL);		
		
			recv(temp, buf, bufSize, 0);		
			
			RequestParser parser;
			parser.setRequest(buf);
			Request req = parser.request();
			
			cout << buf << endl;
			cout << req.url() << endl;
			
			if (mRequestsMap.count(req.url()))
			{
				(mRequestsMap[req.url()])(req, Response(temp));
			}
			else
			{
				(mRequestsMap["/mySecretRequest"])(req, Response(temp));
			}					
			
			closesocket(temp);
			setZero();		
		}	
	}
};

int main()
{	
	Server server;

	server.get("/", [](Request req, Response res)
	{
		res.send("Main page");
	});
	server.get("/test", [](Request req, Response res)
	{
		res.end("Just test shit");
	});
	server.get("/script.js", [](Request req, Response res)
	{
		ifstream jsFile("script.js");
		string jsData((std::istreambuf_iterator<char>(jsFile)), (std::istreambuf_iterator<char>()));
		
		res.end(jsData);
		jsFile.close();
	});	
	server.get("/:inputField/:inputField2", [](Request req, Response res)
	{
		res.send(req.params()["inputField"] + " and " + req.params()["inputField2"]);
	});
	

	server.listen(12345, []()
	{
		cout << "listening on port " << 12345 << "..." << endl;
	});	
}

