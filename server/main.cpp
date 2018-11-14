#include <fstream>
#include <vector>
#include "Server.hpp"


#include <dirent.h>
class VEngine
{
	std::string mPath;
	std::vector<std::string> mViews;
	static const std::string mExpansions[];
public:
	enum EngineType
	{
		html,
		js,
		css
	};

	VEngine(std::string path, EngineType type) : mPath(path)
	{
		DIR *pd = opendir(path.c_str());
		if (!pd)
		{
			throw "open dir error";
		}

		struct dirent *dir;
		while (dir = readdir(pd))
		{
			if (isFile(dir->d_name, type))
			{
				mViews.push_back(std::string(dir->d_name));
			}
		}
		closedir(pd);
	}

	bool isFile(const char*file, EngineType type)
	{
		return std::string(file).find(mExpansions[type]) != std::string::npos;
	}

	std::string getFile(std::string fileName)
	{
		std::ifstream file((mPath + "/" + fileName).c_str());
		std::string data((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		file.close();

		return data;
	}
};
const std::string VEngine::mExpansions[]= {".html", ".js", ".css"};

int main()
{	
	Server server;

	VEngine htmlEngine("../client/views", VEngine::EngineType::html);
	server.get("/", [&htmlEngine](Request req, Response res)
	{
		res.send(htmlEngine.getFile("index.html"));
	});

	VEngine jsEngine("../client/scripts", VEngine::EngineType::js);
	server.get("/script.js", [&jsEngine](Request req, Response res)
	{
		res.send(jsEngine.getFile("script.js"));
	});	

	VEngine cssEngine("../client/styles", VEngine::EngineType::css);
	server.get("/style.css", [&cssEngine](Request req, Response res)
	{
		res.end(cssEngine.getFile("style.css"));
	});	




	server.get("/test", [](Request req, Response res)
	{
		res.send("Just test shit");
	});
	
	server.get("/:inputField/:inputField2", [](Request req, Response res)
	{
		res.send(req.params("inputField") + " and " + req.params("inputField2"));
	});
	
	int port = 12345;
	server.listen(port, [port]()
	{
		std::cout << "listening on port " << port << "..." << std::endl;
	});	
}