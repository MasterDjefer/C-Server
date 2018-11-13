#include <iostream>
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
public:
	Request(string method, string url) : mMethod(method), mUrl(url)
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
};
class Response
{
	SOCKET mSock;
	string mPage;
	string mText;
public:
	Response(SOCKET sock) : mSock(sock)
	{		
	}

	void send(string msg)
	{
		resetPage(msg);
		::send(mSock, mPage.c_str(), mPage.size(), 0);
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
				"</body>" 
			"</html>";
	}
};

class RequestParser
{
	char mRequest[1000];
	char mMethod[10];
	char mUrl[100];
	
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
		return Request(string(mMethod), string(mUrl));
	}	
};


class Server
{
	SOCKET sock;
	sockaddr_in sockAddr;
	const int bufSize = 1000;
	char buf[1000];
	map<string, RequestCallback> mRequestsMap;

	RequestParser parser;

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
			res.send("can'\t get " + req.url());
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
			
			parser.setRequest(buf);
			Request req = parser.request();
			
			if (mRequestsMap.count(req.url()))
			{
				(mRequestsMap[req.url()])(req, Response(temp));
			}
			else
			{
				(mRequestsMap["/mySecretRequest"])(req, Response(temp));
			}		
			
			
			// send(temp, page.c_str(), page.size(), 0);
			closesocket(temp);
			setZero();		
		}	
	}
};

int main()
{	
	Server server;

	server.get("/rock", [](Request req, Response res)
	{
		res.send("roll");
	});

	server.listen(12345, []()
	{
		cout << "listening on port " << 12345 << "..." << endl;
	});	
}

