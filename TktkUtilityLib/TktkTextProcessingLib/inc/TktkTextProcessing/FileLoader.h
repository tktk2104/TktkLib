#ifndef FILE_LOADER_H_
#define FILE_LOADER_H_

#include <string>
#include <vector>

class FileLoader
{
public:

	// 引数のファイルの行ごとデータをstring型のvectorに入れる
	// 読み込みに失敗した場合はfalseが返る
	static bool fileLoad(const std::string& filePath, std::vector<std::string>* out);
};
#endif // !FILE_LOADER_H_