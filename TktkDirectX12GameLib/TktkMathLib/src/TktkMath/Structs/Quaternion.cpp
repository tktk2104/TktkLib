#include "TktkMath/Structs/Quaternion.h"

namespace tktkMath
{
	std::string Quaternion::toString() const
	{
		return "[x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + ", w:" + std::to_string(w) + "]";;
	}

	std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
	{
		return os << quaternion.toString();
	}
}