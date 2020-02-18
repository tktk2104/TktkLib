#include "TktkTextProcessing/FileLoader.h"

#include <fstream>

bool FileLoader::fileLoad(const std::string & filePath, std::vector<std::string>* out)
{
	std::ifstream ifs(filePath.c_str());

	if (!ifs.is_open()) return false;

	std::string line;

	while (std::getline(ifs, line))
	{
		out->push_back(line);
	}

	return true;
}
