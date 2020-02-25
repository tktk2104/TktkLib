#ifndef TEXT_SPLITER_H_
#define TEXT_SPLITER_H_

#include <string>
#include <vector>

class TextSpliter
{
public:

	// 引数の文字列を引数の文字で区切ったデータをstring型のvectorに入れる
	// １度でも区切れたらtrue、区切れなかったらfalseが返る
	static bool textSplit(const std::string& beforSplitText, char spritChar, std::vector<std::string>* out);
};
#endif // !TEXT_SPLITER_H_