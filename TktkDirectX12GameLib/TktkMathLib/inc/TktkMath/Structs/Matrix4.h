#ifndef MATRIX_4_H_
#define MATRIX_4_H_

#include <ostream>

namespace tktkMath
{
	struct Vector3;
	struct Quaternion;

	struct Matrix4
	{
	public:

		// �R���X�g���N�^
		constexpr Matrix4() = default;
		constexpr Matrix4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
			m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
		}

	public:

		// �ړ��s��𐶐�
		static Matrix4 createTranslation(const Vector3& translation);
		// �N�I�[�^�j�I�������]�s��𐶐�
		static Matrix4 createFromQuaternion(const Quaternion& rotate);
		// x���̉�]�s��𐶐�
		static Matrix4 createRotationX(float degree);
		// y���̉�]�s��𐶐�
		static Matrix4 createRotationY(float degree);
		// z���̉�]�s��𐶐�
		static Matrix4 createRotationZ(float degree);
		// ���[�A�s�b�`�A���[���ŉ�]�s��𐶐�
		static Matrix4 createFromYawPitchRoll(float yaw, float pitch, float roll);
		// �C�ӂ̎��̉�]�s��𐶐�
		static Matrix4 createFromAxisAngle(const Vector3& axis, float degree);
		// �X�P�[���s��𐶐�
		static Matrix4 createScale(const Vector3& scale);
		// �ړ��A��]�A�X�P�[���̒l����s��𐶐�
		static Matrix4 createTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// �t�s����v�Z
		static Matrix4 calculateInvert(const Matrix4& matrix);
		// �����t�������A�t�s��������Ōv�Z�i��]�ƕ��s�ړ��̂݁j
		static Matrix4 calculateInvertFast(const Matrix4& matrix);
		// �]�u�s����v�Z
		static Matrix4 calculateTranspose(const Matrix4& matrix);
		// 2�̍s��̑Ή�����l�̊Ԃ���`��Ԃ��܂�
		static Matrix4 lerp(const Matrix4& value1, const Matrix4& value2, float amount);
		// ��]�s��𐳋K�����܂��B
		static Matrix4 normalizeRotationMatrix(const Matrix4& matrix);
		// �X�N���[�����W�n�ɕϊ�����s��𐶐�
		static Matrix4 createScreen(float x, float y, float width, float height);
		// ������W�n�̃r���[�s��𐶐��iDirectX���j
		static Matrix4 createLookAtLH(const Vector3& position, const Vector3& target, const Vector3& up);
		// �E����W�n�̃r���[�s��𐶐��iOpenGL���j
		static Matrix4 createLookAtRH(const Vector3& position, const Vector3& target, const Vector3& up);
		// ������W�n�̕��s���e�s��𐶐��iDirectX���j
		static Matrix4 createOrthographicLH(float width, float height, float zn, float zf);
		// ������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iDirectX���j
		static Matrix4 createPerspectiveFieldOfViewLH(float fov, float aspect, float zn, float zf);
		// �E����W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iOpenGL���j
		static Matrix4 createPerspectiveFieldOfViewRH(float fov, float aspect, float zn, float zf);

	public:

		// �ړ��̒l���Đݒ�
		void setTranslation(const Vector3& translation);
		// �ړ��A��]�A�X�P�[���̒l���Đݒ�
		void setTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// ���W���v�Z
		Vector3 calculateTranslation() const;
		// ��]���v�Z
		Quaternion calculateRotation() const;
		// �X�P�[���l���v�Z
		Vector3 calculateScale() const;
		// ������W�n�̑O���x�N�g�����v�Z�iDirectX���j
		Vector3 calculateForwardLH() const;
		// �E����W�n�̑O���x�N�g�����v�Z�iOpenGL���j
		Vector3 calculateForwardRH() const;
		// ����x�N�g�����v�Z
		Vector3 calculateUp() const;
		// �E�x�N�g�����v�Z
		Vector3 calculateRight() const;
		// �t�s����v�Z
		Matrix4 calculateInvert() const;
		// �]�u�s����v�Z
		Matrix4 calculateTranspose() const;
		// ���W�ϊ��i�ʏ�j
		Vector3 multiplyPoint(const Vector3& point);
		// ���W�ϊ��i�����j
		Vector3 multiplyPointFast(const Vector3& point);
		// �x�N�g���ϊ��i���s�ړ������j
		Vector3 multiplyVector(const Vector3& vector);
		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		// �e�v�f
		float m[4][4]{
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};
	};

	// Matrix4�\���̂̒萔�B
	struct Matrix4_v
	{
		static constexpr Matrix4 zero {
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		};

		static constexpr Matrix4 identity {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	};

	// �萔�B�i�񐄏��F�uMatrix4_v::�v���g���Ă��������j
	constexpr Matrix4 mat4Zero		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix4 mat4Identity	{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	Matrix4			operator - (const Matrix4& v);
	Matrix4&		operator += (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator -= (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator *= (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator *= (Matrix4& m, float s);
	Matrix4&		operator /= (Matrix4& m, float s);
	Matrix4			operator * (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator * (Matrix4 m, float s);
	Matrix4			operator * (Matrix4 s, float m);
	Vector3			operator * (const Vector3& v, const Matrix4& m);
	Matrix4			operator + (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator - (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator * (Matrix4 m, float s);
	Matrix4			operator * (float s, Matrix4 m);
	Matrix4			operator / (Matrix4 m, float s);
	std::ostream&	operator<<(std::ostream& os, const Matrix4& matrix);
}
#endif // !MATRIX_4_H_