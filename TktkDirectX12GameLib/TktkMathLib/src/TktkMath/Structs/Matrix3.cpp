#include "TktkMath/Structs/Matrix3.h"

namespace tktkMath
{
	// TODO : é¿ëïÇçlÇ¶ÇÈ
	//Matrix3 Matrix3::calculateInvertFast(const Matrix3 & matrix)
	//{
	//	Matrix3 invRotation = Matrix3::transpose(Matrix3(matrix).translation(Vector2::zero));
	//
	//	//Vector2 invTranslation = Vector2
	//
	//	return matrix;
	//}

	std::string Matrix3::toString() const
	{
		return "[ m11:" + std::to_string(m[0][0]) + ", m12:" + std::to_string(m[0][1]) + ", m13:" + std::to_string(m[0][2]) + "\n"
			+ ", m21:" + std::to_string(m[1][0]) + ", m22:" + std::to_string(m[1][1]) + ", m23:" + std::to_string(m[1][2]) + "\n"
			+ ", m31:" + std::to_string(m[2][0]) + ", m32:" + std::to_string(m[2][1]) + ", m33:" + std::to_string(m[2][2]) + "]";
	}

	std::ostream& operator<<(std::ostream& os, const Matrix3& matrix)
	{
		return os << matrix.toString();
	}
}