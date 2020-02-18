#ifndef EXTENSION_GETTER_H_
#define EXTENSION_GETTER_H_

#include <string>

class ExtensionGetter
{
public:

	static bool get(const std::string& fileName, std::string* out);
};

#endif // !EXTENSION_GETTER_H_
