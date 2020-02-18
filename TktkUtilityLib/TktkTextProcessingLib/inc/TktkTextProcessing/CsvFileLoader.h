#ifndef CSV_FILE_LOADER_H_
#define CSV_FILE_LOADER_H_

#include <string>
#include <vector>

namespace tktk
{
	class CsvFileLoader
	{
	public:

		struct OutPutData
		{
			std::vector<std::vector<std::string>> data;
		};

		static bool fileLoad(const std::string& filePath, OutPutData* out);

	private:

		static void pushSplitWordData(const std::string& lineData, OutPutData * out);
	};
}
#endif // !CSV_FILE_LOADER_H_