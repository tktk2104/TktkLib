#include "TktkMath/Structs/Matrix4.h"

namespace tktkMath
{
	std::string Matrix4::toString() const
	{
		return	"[ m11:" + std::to_string(m[0][0]) + ", m12:" + std::to_string(m[0][1]) + ", m13:" + std::to_string(m[0][2]) + ", m14:" + std::to_string(m[0][3]) + "\n"
			+	", m21:" + std::to_string(m[1][0]) + ", m22:" + std::to_string(m[1][1]) + ", m23:" + std::to_string(m[1][2]) + ", m24:" + std::to_string(m[1][3]) + "\n"
			+	", m31:" + std::to_string(m[2][0]) + ", m32:" + std::to_string(m[2][1]) + ", m33:" + std::to_string(m[2][2]) + ", m34:" + std::to_string(m[2][3]) + "\n"
			+	", m41:" + std::to_string(m[3][0]) + ", m42:" + std::to_string(m[3][1]) + ", m43:" + std::to_string(m[3][2]) + ", m44:" + std::to_string(m[3][3]) + "]";
	}

	std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
	{
		return os << matrix.toString();
	}
}