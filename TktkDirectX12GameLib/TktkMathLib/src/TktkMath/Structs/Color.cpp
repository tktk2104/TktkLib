#include "TktkMath/Structs/Color.h"

namespace tktkMath
{
	std::string Color::toString() const
	{
		return  "[red:"		+ std::to_string(r)
			  + ", green:"	+ std::to_string(g)
			  + ", blue:"	+ std::to_string(b)
			  + ", alpha:"	+ std::to_string(a)
			  + "]";
	}

	std::ostream & operator<<(std::ostream & os, const Color & color)
	{
		return os << color.toString();
	}
}