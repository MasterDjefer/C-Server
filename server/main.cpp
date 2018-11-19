#include <fstream>
#include "Server.hpp"
#include "VEngine.hpp"

int main() 
{	
	Server server;

	VEngine htmlEngine("../client/views", VEngine::EngineType::html);
	server.get("/", [&htmlEngine](Request req, Response res)
	{
		res.send(htmlEngine.getFile("index"), Response::ResponseType::html);
	});

	VEngine jsEngine("../client/scripts", VEngine::EngineType::js);
	server.get("/script.js", [&jsEngine](Request req, Response res)
	{
		res.send(jsEngine.getFile("script"), Response::ResponseType::js);
	});	

	VEngine cssEngine("../client/styles", VEngine::EngineType::css);
	server.get("/style.css", [&cssEngine](Request req, Response res)
	{
		res.send(cssEngine.getFile("style"), Response::ResponseType::css);
	});	



	
	VEngine jpgEngine("../client/images", VEngine::EngineType::jpg);
	server.get("/deadpool.jpg", [&jpgEngine](Request req, Response res)
	{		
		res.send(jpgEngine.getFile("deadpool.jpg"), Response::ResponseType::jpg);
	});	
	VEngine icoEngine("../client/images", VEngine::EngineType::ico);
	server.get("/favicon.ico", [&icoEngine](Request req, Response res)
	{		
		res.send(icoEngine.getFile("favicon"), Response::ResponseType::ico);
	});	




	server.get("/test/:variable", [](Request req, Response res)
	{
		res.send(req.params("variable") + " is shit", Response::ResponseType::html);
	});	
	server.get("/:name/:age", [](Request req, Response res)
	{
		res.send(req.params("name") + " is " + req.params("age"), Response::ResponseType::html);
	});

	server.post("/me", [](Request req, Response res)
	{
		res.send(req.body("name") + " is " + req.body("age"), Response::ResponseType::html);		
	});

	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}
