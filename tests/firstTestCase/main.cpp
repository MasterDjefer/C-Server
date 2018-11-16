#include <fstream>
#include "Server.hpp"
 
int main()
{	
	Server server;

	server.get("/", [](Request req, Response res)
	{
		res.end("Main page");
	});

	server.get("/test/:variable", [](Request req, Response res)
	{
		res.end(req.params("variable") + " is shit");
	});	
	server.get("/:name/:age", [](Request req, Response res)
	{
		res.end(req.params("name") + " is " + req.params("age"));
	});

	server.post("/me", [](Request req, Response res)
	{
		res.end(req.body("name") + " is " + req.body("age"));		
	});

	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}