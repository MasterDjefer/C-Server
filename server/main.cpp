#include <fstream>
#include "Server.hpp"
#include "VEngine.hpp"

int main()
{	
	Server server;

	VEngine htmlEngine("../client/views", VEngine::EngineType::html);
	server.get("/", [&htmlEngine](Request req, Response res)
	{
		res.send(htmlEngine.getFile("index"));
	});

	VEngine jsEngine("../client/scripts", VEngine::EngineType::js);
	server.get("/script.js", [&jsEngine](Request req, Response res)
	{
		res.send(jsEngine.getFile("script"));
	});	

	VEngine cssEngine("../client/styles", VEngine::EngineType::css);
	server.get("/style.css", [&cssEngine](Request req, Response res)
	{
		res.end(cssEngine.getFile("style"));
	});	




	server.get("/test/:variable", [](Request req, Response res)
	{
		res.send(req.params("variable") + " is shit");
	});	
	server.get("/:name/:age", [](Request req, Response res)
	{
		res.send(req.params("name") + " is " + req.params("age"));
	});

	server.post("/me", [](Request req, Response res)
	{
		res.send(req.body("name") + " is " + req.body("age"));		
	});

	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}