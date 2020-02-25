#ifndef TEXT_CHAR_DELETER_H_
#define TEXT_CHAR_DELETER_H_

#include <string>
#include <vector>

class TextCharDeleter
{
public:

	// 引数の文字列から引数の文字を削除する
	// 削除できたらtrue、削除できなかったらfalseが返る
	static bool textCharDelete(const std::string& beforDeleteText, char deleteChar, std::string* out);

	// 引数の文字列から引数の文字の配列の要素全てを削除する
	// 削除できたらtrue、削除できなかったらfalseが返る
	static bool textCharDelete(const std::string& beforDeleteText, std::vector<char> deleteChars, std::string* out);
};
#endif // !TEXT_CHAR_DELETER_H_