#include "TktkConstexprMath/Structs/ConstexprVector3.h"

namespace tktkConstexprMath
{
	std::string Vector3::toString() const
	{
		return "[x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + "]";
	}

	std::ostream & operator<<(std::ostream & os, const Vector3 & vector3)
	{
		return os << vector3.toString();
	}
}