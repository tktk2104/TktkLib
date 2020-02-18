#include "TktkTextProcessing/ExtensionGetter.h"

bool ExtensionGetter::get(const std::string & fileName, std::string * out)
{
	*out = fileName.substr(fileName.size() - 3U, 3U);
	return true;
}
