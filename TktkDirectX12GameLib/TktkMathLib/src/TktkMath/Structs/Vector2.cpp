#include "TktkMath/Structs/Vector2.h"

namespace tktkMath
{
	std::string Vector2::toString() const
	{
		return  "[x:" + std::to_string(x) + ", y:" + std::to_string(y) + "]";
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
	{
		return os << vector2.toString();
	}
}