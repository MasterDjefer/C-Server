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
void Server::get(std::string url, RequestCallback callback)
{
	mRequestsMap.insert(std::pair<std::string, RequestCallback>(url, callback));
}
void Server::setZero()
{
	memset(buf, 0, bufSize);
}

void Server::acceptConnection()
{
	SOCKET temp;
	while (true)
	{
		temp = accept(sock, NULL, NULL);		
	
		recv(temp, buf, bufSize, 0);		
		
		RequestParser parser;
		parser.setRequest(buf);
		Request req = parser.request();
		
		//cout << buf << endl;
		std::cout << req.url() << std::endl;
		
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