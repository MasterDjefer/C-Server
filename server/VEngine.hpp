#ifndef VENGINE_H
#define VENGINE_H
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <dirent.h>

class VEngine
{
public:
	enum EngineType
	{
		html,
		js,
		css
	};

private:
	std::string mPath;
	std::vector<std::string> mViews;
	static const std::string mExpansions[];
	EngineType mType;

public:
	VEngine(std::string path, EngineType type);
	std::string getFile(std::string fileName);

private:
	bool isFile(const char*file);
};
#endif