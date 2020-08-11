#ifndef MATRIX3_H_
#define MATRIX3_H_

#include <ostream>

namespace tktkMath
{
	struct Vector2;

	// 3x3�̍s��̍\����
	struct Matrix3
	{
	public:

		// �R���X�g���N�^
		constexpr Matrix3() = default;
		constexpr Matrix3(
			float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
		}

	public:

		// �ړ��s��𐶐�
		static Matrix3 createTranslation(const Vector2& translation);
		// ��]�s��𐶐�
		static Matrix3 createRotation(float degree);
		// �X�P�[���s��𐶐�
		static Matrix3 createScale(const Vector2& scale);
		// �ړ��A��]�A�X�P�[���̒l����s��𐶐�
		static Matrix3 createTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// �t�s��𐶐�
		static Matrix3 calculateInvert(const Matrix3& matrix);
		// �s��̍s�Ɨ�����ւ��܂��B
		static Matrix3 calculateTranspose(const Matrix3& matrix);

	public:

		// ���s�ړ��x�N�g����ݒ�
		void setTranslation(const Vector2& translation);
		// �ړ��A��]�A�X�P�[���̒l���Đݒ�
		void setTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// ���s�ړ��x�N�g�����v�Z
		Vector2 calculateTranslation() const;
		// ��]���v�Z
		float calculateRotation() const;
		// �X�P�[���l���v�Z
		Vector2 calculateScale() const;
		// ����x�N�g�����v�Z
		Vector2 calculateUp() const;
		// �E�x�N�g�����v�Z
		Vector2 calculateRight() const;
		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		// �e�v�f
		float m[3][3]{
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f }
		};
	};

	// Matrix3�\���̂̒萔�B
	struct Matrix3_v
	{
		static constexpr Matrix3 zero {
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

		static constexpr Matrix3 identity {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
	};

	// �萔�B�i�񐄏��F�uMatrix3_v::�v���g���Ă��������j
	constexpr Matrix3 mat3Zero{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix3 mat3Identity{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	Matrix3			operator -  (const Matrix3& m);
	Matrix3&		operator += (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator -= (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator *= (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator *= (Matrix3& m, float s);
	Matrix3&		operator /= (Matrix3& m, float s);
	Matrix3			operator +  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator -  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator *  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator *  (Matrix3 m, float s);
	Matrix3			operator *  (float s, Matrix3 m);
	Matrix3			operator /  (Matrix3 m, float s);
	Vector2			operator *	(const Vector2& v, const Matrix3& m);
	Vector2&		operator *=	(Vector2& v, const Matrix3& m);
	std::ostream&	operator << (std::ostream& os, const Matrix3& matrix);
}
#endif