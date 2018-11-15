#include "VEngine.hpp"

VEngine::VEngine(std::string path, EngineType type) : mPath(path), mType(type)
{
	DIR *pd = opendir(path.c_str());
	if (!pd)
	{
		throw "open dir error";
	}

	struct dirent *dir;
	while (dir = readdir(pd))
	{
		if (isFile(dir->d_name))
		{
			mViews.push_back(std::string(dir->d_name));
		}
	}
	closedir(pd);
}
std::string VEngine::getFile(std::string fileName)
{
	if (fileName.find(".") == std::string::npos)
	{
		fileName += mExpansions[mType];
	}
	
	if (std::find(mViews.begin(), mViews.end(), fileName) == mViews.end())
		throw "fileName error";

	std::ifstream file((mPath + "/" + fileName).c_str());
	std::string data((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	file.close();

	return data;
}
bool VEngine::isFile(const char*file)
{
	return std::string(file).find(mExpansions[mType]) != std::string::npos;
}

const std::string VEngine::mExpansions[]= {".html", ".js", ".css"};