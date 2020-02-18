#include "TktkTextProcessing/CsvFileLoader.h"

#include <algorithm>
#include "TktkTextProcessing/FileLoader.h"
#include "TktkTextProcessing/TextSpliter.h"

namespace tktk
{
	bool CsvFileLoader::fileLoad(const std::string & filePath, OutPutData * out)
	{
		out->data.clear();

		std::vector<std::string> loadFileData;
		if (!FileLoader::fileLoad(filePath, &loadFileData)) return false;

		std::for_each(
			std::begin(loadFileData),
			std::end(loadFileData),
			[&out](const auto& node) { pushSplitWordData(node, out); }
		);
		return true;
	}

	void CsvFileLoader::pushSplitWordData(const std::string & lineData, OutPutData * out)
	{
		std::vector<std::string> splitWordData;
		TextSpliter::textSplit(lineData, ',', &splitWordData);
		out->data.push_back(splitWordData);
	}
}