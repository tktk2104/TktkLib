#include "TktkTextProcessing/TextCharDeleter.h"

bool TextCharDeleter::textCharDelete(const std::string & beforDeleteText, char deleteChar, std::string * out)
{
	(*out) = beforDeleteText;

	bool deleted = false;

	size_t c;

	while ((c = (*out).find_first_of(deleteChar)) != std::string::npos)
	{
		(*out).erase(c, 1);
		deleted = true;
	}

	return deleted;
}

bool TextCharDeleter::textCharDelete(const std::string & beforDeleteText, std::vector<char> deleteChars, std::string * out)
{
	(*out) = beforDeleteText;

	bool deleted = false;

	for (const auto & deleteChar : deleteChars)
	{
		std::string curDeleteText = (*out);

		if (textCharDelete(curDeleteText, deleteChar, out)) deleted = true;
	}
	return deleted;
}
