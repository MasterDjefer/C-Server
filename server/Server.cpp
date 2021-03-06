#include "Server.hpp"

Server::Server()
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
Server::~Server()
{
	closesocket(sock);
	WSACleanup();
}
void Server::listen(int port, Func f = NULL)
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

	if (f)
	{
		f();
	}
	acceptConnection();
}
void Server::defunctRequest(Request req, Response res)
{
	res.setStatus(404);
	res.send("can\'t " + req.method() + " " + req.url(), Response::ResponseType::html);
}
void Server::get(std::string url, RequestCallback callback)
{
	mGetRequestsMap.insert(std::pair<std::string, RequestCallback>(url, callback));
}
void Server::post(std::string url, RequestCallback callback)
{
	mPostRequestsMap.insert(std::pair<std::string, RequestCallback>(url, callback));
}
void Server::setZero()
{
	memset(buf, 0, bufSize);
}
void Server::acceptConnection()
{
	while (true)
	{
		SOCKET temp = accept(sock, NULL, NULL);
	
		int res = recv(temp, buf, bufSize, 0);//sometimes can read 0 bytes, so it needs to get next iteration(continue)(fixed)
		if (res == SOCKET_ERROR)
		{
			std::cout << "error" << std::endl;
			continue;
		} 
		else if (res == 0)//fix bag with timeout(i need bliakhovskyi's help(just ask))   //SERVER terminated connection
		{
			std::cout << "disconnect(timeout recv)" << std::endl;
			continue;
		}


		if (std::string(buf) == "EXIT")
		{
			exit(1);
		}		
		
		RequestParser parser;
		parser.setRequest(buf);
		Request req = parser.request();
		// std::cout << buf << std::endl;
		
		std::cout << req.method() << " " << req.url() << std::endl;
		
		if (req.method() == "GET")
		{
			if (mGetRequestsMap.count(req.url()))
			{
				(mGetRequestsMap[req.url()])(req, Response(temp));
			}
			else
			{
				defunctRequest(req, Response(temp));
			}	
		}
		else
		if (req.method() == "POST")			
		{
			if (mPostRequestsMap.count(req.url()))
			{
				(mPostRequestsMap[req.url()])(req, Response(temp));
			}
			else
			{
				defunctRequest(req, Response(temp));
			}
		}	
		
		closesocket(temp);
		setZero();		
	}	
}
