#include <fstream>
#include <cstdio>
#include "Server.hpp"
#include "VEngine.hpp"


struct color {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};
struct image {
	char header[54];
	color data[480][640];
};



int main() 
{	
	Server server;

	VEngine htmlEngine("../client/views", VEngine::EngineType::html);
	server.get("/", [&htmlEngine](Request req, Response res)
	{
		res.send(htmlEngine.getFile("index"), Response::TextType::html);
	});

	VEngine jsEngine("../client/scripts", VEngine::EngineType::js);
	server.get("/script.js", [&jsEngine](Request req, Response res)
	{
		res.send(jsEngine.getFile("script"), Response::TextType::js);
	});	

	VEngine cssEngine("../client/styles", VEngine::EngineType::css);
	server.get("/style.css", [&cssEngine](Request req, Response res)
	{
		res.send(cssEngine.getFile("style"), Response::TextType::css);
	});	


	server.get("/deadpool.jpg", [](Request req, Response res)
	{
		// std::ifstream input_image ("..\\client\\images\\deadpool.jpg");
		// res.end("..\\client\\images\\deadpool.jpg");
	});	


	server.get("/test/:variable", [](Request req, Response res)
	{
		res.send(req.params("variable") + " is shit", Response::TextType::html);
	});	
	server.get("/:name/:age", [](Request req, Response res)
	{
		res.send(req.params("name") + " is " + req.params("age"), Response::TextType::html);
	});

	server.post("/me", [](Request req, Response res)
	{
		res.send(req.body("name") + " is " + req.body("age"), Response::TextType::html);		
	});

	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}
