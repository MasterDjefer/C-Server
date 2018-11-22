#include <fstream>
#include <vector>
#include <algorithm>
#include "Server.hpp"
#include "VEngine.hpp"

class Person
{
	std::string mName;
	std::string mJob;
public:
	Person()
	{		
	}
	Person(const std::string& name, const std::string& job) : mName(name), mJob(job)
	{
	}
	std::string info() const
	{
		return mName + " - " + mJob;
	}
};


int main() 
{	
	Server server;

	std::vector<Person> persons;

	//pages
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


	//images
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



	//data requests
	server.post("/postData", [&persons](Request req, Response res)
	{
		persons.push_back(Person(req.body("name"), req.body("job")));
		res.send(req.body("name") + " - " + req.body("job"), Response::ResponseType::html);		
	});
	server.get("/getData/:index", [&persons](Request req, Response res)//problem here(request 10times!)
	{
		// std::cout << req.params("index") << std::endl;
		int index = std::stoi(req.params("index"));
		if (index > 0 && index <= persons.size())
			res.send(persons.at(index - 1).info(), Response::ResponseType::html);
		else
			res.send("Invalid index", Response::ResponseType::html);
	});	
	server.get("/getAllData", [&persons](Request req, Response res)
	{
		std::string allData = "";
		std::for_each(persons.begin(), persons.end(), [&allData](const Person& person)
		{
			allData += person.info() + "\n";
		});
		res.send(allData, Response::ResponseType::html);
	});

	
	server.get("/ss", [&persons](Request req, Response res)//problem here(request 10times!)
	{
			res.send("hi", Response::ResponseType::html);
	});	








	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}
