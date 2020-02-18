#include "TktkTextProcessing/TextSpliter.h"

#include <sstream>

bool TextSpliter::textSplit(const std::string & beforSplitText, char spritChar, std::vector<std::string>* out)
{
	out->clear();

	std::istringstream strengStream(beforSplitText);

	std::string afterSpritWord;

	bool splitted = false;

	while (std::getline(strengStream, afterSpritWord, spritChar))
	{
		out->push_back(afterSpritWord);
		splitted = true;
	}

	return splitted;
}