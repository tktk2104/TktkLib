#ifndef MATRIX_4_H_
#define MATRIX_4_H_

#include <string>
#include <ostream>
#include <algorithm>
#include "Vector3.h"
#include "Quaternion.h"
#include "../MathHelper.h"

namespace tktkMath
{
	// 3x3�̍s��̍\����
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
		static constexpr Matrix4 createTranslation(const Vector3& translation);
		// �N�I�[�^�j�I�������]�s��𐶐�
		static constexpr Matrix4 createFromQuaternion(const Quaternion& rotate);
		// x���̉�]�s��𐶐�
		static constexpr Matrix4 createRotationX(float degree);
		// y���̉�]�s��𐶐�
		static constexpr Matrix4 createRotationY(float degree);
		// z���̉�]�s��𐶐�
		static constexpr Matrix4 createRotationZ(float degree);
		// ���[�A�s�b�`�A���[���ŉ�]�s��𐶐�
		static constexpr Matrix4 createFromYawPitchRoll(float yaw, float pitch, float roll);
		// �C�ӂ̎��̉�]�s��𐶐�
		static constexpr Matrix4 createFromAxisAngle(const Vector3& axis, float degree);
		// �X�P�[���s��𐶐�
		static constexpr Matrix4 createScale(const Vector3& scale);
		// �ړ��A��]�A�X�P�[���̒l����s��𐶐�
		static constexpr Matrix4 createTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// �t�s����v�Z
		static constexpr Matrix4 calculateInvert(const Matrix4& matrix);
		// �����t�������A�t�s��������Ōv�Z�i��]�ƕ��s�ړ��̂݁j
		static constexpr Matrix4 calculateInvertFast(const Matrix4& matrix);
		// �]�u�s����v�Z
		static constexpr Matrix4 calculateTranspose(const Matrix4& matrix);
		// 2�̍s��̑Ή�����l�̊Ԃ���`��Ԃ��܂�
		static Matrix4 lerp(const Matrix4& value1, const Matrix4& value2, float amount);
		// ��]�s��𐳋K�����܂�
		static constexpr Matrix4 normalizeRotationMatrix(const Matrix4& matrix);
		// �X�N���[�����W�n�ɕϊ�����s��𐶐�
		static constexpr Matrix4 createScreen(float x, float y, float width, float height);
		// ������W�n�̃r���[�s��𐶐��iDirectX���j
		static constexpr Matrix4 createLookAtLH(const Vector3& position, const Vector3& target, const Vector3& up);
		// �E����W�n�̃r���[�s��𐶐��iOpenGL���j
		static constexpr Matrix4 createLookAtRH(const Vector3& position, const Vector3& target, const Vector3& up);
		// ������W�n�̕��s���e�s��𐶐��iDirectX���j
		static constexpr Matrix4 createOrthographicLH(float width, float height, float zn, float zf);
		// ������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iDirectX���j
		static constexpr Matrix4 createPerspectiveFieldOfViewLH(float fov, float aspect, float zn, float zf);
		// �E����W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iOpenGL���j
		static constexpr Matrix4 createPerspectiveFieldOfViewRH(float fov, float aspect, float zn, float zf);
		// �w�肳�ꂽ Matrix �ɂ���āAVector3���g�����X�t�H�[�����܂�
		static constexpr Vector3 transformVec(const Vector3& position, const Matrix4& matrix);
		// �w�肳�ꂽ Matrix �ɂ���āA�@���x�N�g�����g�����X�t�H�[�����܂�
		static constexpr Vector3 transformVecNormal(const Vector3& position, const Matrix4& matrix);

	public:

		// �ړ��̒l���Đݒ�
		constexpr void setTranslation(const Vector3& translation);
		// �ړ��A��]�A�X�P�[���̒l���Đݒ�
		constexpr void setTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// ���W���v�Z
		constexpr Vector3 calculateTranslation() const;
		// ��]���v�Z
		constexpr Quaternion calculateRotation() const;
		// �X�P�[���l���v�Z
		constexpr Vector3 calculateScale() const;
		// ������W�n�̑O���x�N�g�����v�Z�iDirectX���j
		constexpr Vector3 calculateForwardLH() const;
		// �E����W�n�̑O���x�N�g�����v�Z�iOpenGL���j
		constexpr Vector3 calculateForwardRH() const;
		// ����x�N�g�����v�Z
		constexpr Vector3 calculateUp() const;
		// �E�x�N�g�����v�Z
		constexpr Vector3 calculateRight() const;
		// �t�s����v�Z
		constexpr Matrix4 calculateInvert() const;
		// �]�u�s����v�Z
		constexpr Matrix4 calculateTranspose() const;
		// ���W�ϊ��i�ʏ�j
		constexpr Vector3 multiplyPoint(const Vector3& point);
		// ���W�ϊ��i�����j
		constexpr Vector3 multiplyPointFast(const Vector3& point);
		// �x�N�g���ϊ��i���s�ړ������j
		constexpr Vector3 multiplyVector(const Vector3& vector);

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

	// �萔�B
	constexpr Matrix4 mat4Zero		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix4 mat4Identity	{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	constexpr Matrix4 operator - (const Matrix4& v);
	constexpr Matrix4& operator += (Matrix4& m1, const Matrix4& m2);
	constexpr Matrix4& operator -= (Matrix4& m1, const Matrix4& m2);
	constexpr Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);
	constexpr Matrix4& operator *= (Matrix4& m, float s);
	constexpr Matrix4& operator /= (Matrix4& m, float s);
	constexpr Matrix4  operator * (Matrix4 m1, const Matrix4& m2);
	constexpr Matrix4  operator * (Matrix4 m, float s);
	constexpr Matrix4  operator * (Matrix4 s, float m);
	constexpr Vector3 operator * (const Vector3& v, const Matrix4& m);
	constexpr Matrix4 operator + (Matrix4 m1, const Matrix4& m2);
	constexpr Matrix4 operator - (Matrix4 m1, const Matrix4& m2);
	constexpr Matrix4 operator * (Matrix4 m, float s);
	constexpr Matrix4 operator * (float s, Matrix4 m);
	constexpr Matrix4 operator / (Matrix4 m, float s);
	std::ostream& operator<<(std::ostream& os, const Matrix4& matrix);

//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �ړ��s��𐶐�
	inline constexpr Matrix4 Matrix4::createTranslation(const Vector3& translation)
	{
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			translation.x, translation.y, translation.z, 1.0f
		);
	}
	// �N�I�[�^�j�I�������]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createFromQuaternion(const Quaternion& rotate)
	{
		float xx = rotate.x * rotate.x * 2.0f;
		float yy = rotate.y * rotate.y * 2.0f;
		float zz = rotate.z * rotate.z * 2.0f;
		float xy = rotate.x * rotate.y * 2.0f;
		float xz = rotate.x * rotate.z * 2.0f;
		float yz = rotate.y * rotate.z * 2.0f;
		float wx = rotate.w * rotate.x * 2.0f;
		float wy = rotate.w * rotate.y * 2.0f;
		float wz = rotate.w * rotate.z * 2.0f;

		return Matrix4(
			1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
			xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
			xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	// x���̉�]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createRotationX(float degree)
	{
		float sin = helper::sin(degree);
		float cos = helper::cos(degree);
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,  cos,  sin, 0.0f,
			0.0f, -sin,  cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	// y���̉�]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createRotationY(float degree)
	{
		float sin = helper::sin(degree);
		float cos = helper::cos(degree);
		return Matrix4(
			 cos, 0.0f, -sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			 sin, 0.0f,  cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	// z���̉�]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createRotationZ(float degree)
	{
		float sin = helper::sin(degree);
		float cos = helper::cos(degree);
		return Matrix4(
			 cos,  sin, 0.0f, 0.0f,
			-sin,  cos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	// ���[�A�s�b�`�A���[���ŉ�]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		return Matrix4::createRotationZ(roll)
			 * Matrix4::createRotationX(pitch)
			 * Matrix4::createRotationY(yaw);
	}
	// �C�ӂ̎��̉�]�s��𐶐�
	inline constexpr Matrix4 Matrix4::createFromAxisAngle(const Vector3& axis, float degree)
	{
		return createFromQuaternion(Quaternion::createFromAxisAngle(axis, degree));
	}
	// �X�P�[���s��𐶐�
	inline constexpr Matrix4 Matrix4::createScale(const Vector3& scale)
	{
		return Matrix4(
			scale.x,    0.0f,    0.0f, 0.0f,
			   0.0f, scale.y,    0.0f, 0.0f,
			   0.0f,    0.0f, scale.z, 0.0f,
			   0.0f,    0.0f,    0.0f, 1.0f
		);
	}
	// �ړ��A��]�A�X�P�[���̒l����s��𐶐�
	inline constexpr Matrix4 Matrix4::createTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale)
	{
		Matrix4 result = createFromQuaternion(rotate);

		result.m[0][0] *= scale.x;			result.m[0][1] *= scale.x;			result.m[0][2] *= scale.x;
		result.m[1][0] *= scale.y;			result.m[1][1] *= scale.y;			result.m[1][2] *= scale.y;
		result.m[2][0] *= scale.z;			result.m[2][1] *= scale.z;			result.m[2][2] *= scale.z;
		result.m[3][0] = translation.x;		result.m[3][1] = translation.y;		result.m[3][2] = translation.z;

		return result;
	}
	// �t�s����v�Z
	inline constexpr Matrix4 Matrix4::calculateInvert(const Matrix4& matrix)
	{
		float a0 = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];
		float a1 = matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0];
		float a2 = matrix.m[0][0] * matrix.m[1][3] - matrix.m[0][3] * matrix.m[1][0];
		float a3 = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];
		float a4 = matrix.m[0][1] * matrix.m[1][3] - matrix.m[0][3] * matrix.m[1][1];
		float a5 = matrix.m[0][2] * matrix.m[1][3] - matrix.m[0][3] * matrix.m[1][2];
		float b0 = matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0];
		float b1 = matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0];
		float b2 = matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0];
		float b3 = matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1];
		float b4 = matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1];
		float b5 = matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2];

		float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		if (det == 0.0f)
		{
			return matrix; // �t�s�񂪑��݂��Ȃ��I
		}

		float invDet = 1.0f / det;

		return Matrix4(
			( matrix.m[1][1] * b5 - matrix.m[1][2] * b4 + matrix.m[1][3] * b3) * invDet,
			(-matrix.m[0][1] * b5 + matrix.m[0][2] * b4 - matrix.m[0][3] * b3) * invDet,
			( matrix.m[3][1] * a5 - matrix.m[3][2] * a4 + matrix.m[3][3] * a3) * invDet,
			(-matrix.m[2][1] * a5 + matrix.m[2][2] * a4 - matrix.m[2][3] * a3) * invDet,
			(-matrix.m[1][0] * b5 + matrix.m[1][2] * b2 - matrix.m[1][3] * b1) * invDet,
			( matrix.m[0][0] * b5 - matrix.m[0][2] * b2 + matrix.m[0][3] * b1) * invDet,
			(-matrix.m[3][0] * a5 + matrix.m[3][2] * a2 - matrix.m[3][3] * a1) * invDet,
			( matrix.m[2][0] * a5 - matrix.m[2][2] * a2 + matrix.m[2][3] * a1) * invDet,
			( matrix.m[1][0] * b4 - matrix.m[1][1] * b2 + matrix.m[1][3] * b0) * invDet,
			(-matrix.m[0][0] * b4 + matrix.m[0][1] * b2 - matrix.m[0][3] * b0) * invDet,
			( matrix.m[3][0] * a4 - matrix.m[3][1] * a2 + matrix.m[3][3] * a0) * invDet,
			(-matrix.m[2][0] * a4 + matrix.m[2][1] * a2 - matrix.m[2][3] * a0) * invDet,
			(-matrix.m[1][0] * b3 + matrix.m[1][1] * b1 - matrix.m[1][2] * b0) * invDet,
			( matrix.m[0][0] * b3 - matrix.m[0][1] * b1 + matrix.m[0][2] * b0) * invDet,
			(-matrix.m[3][0] * a3 + matrix.m[3][1] * a1 - matrix.m[3][2] * a0) * invDet,
			( matrix.m[2][0] * a3 - matrix.m[2][1] * a1 + matrix.m[2][2] * a0) * invDet
		);
	}
	// �����t�������A�t�s��������Ōv�Z�i��]�ƕ��s�ړ��̂݁j
	inline constexpr Matrix4 Matrix4::calculateInvertFast(const Matrix4& matrix)
	{
		// ��]�s��̋t�s����쐬
		Matrix4 useRotationMat = matrix;
		useRotationMat.setTranslation(vec3Zero);
		Matrix4 inv_rotation = Matrix4::calculateTranspose(useRotationMat);

		// ���s�ړ������̋t�ϊ�
		Vector3 inv_translation = transformVec(-matrix.calculateTranslation(), inv_rotation);

		// �t�s����쐬
		inv_rotation.setTranslation(inv_translation);
		return inv_rotation;
	}
	// �]�u�s����v�Z
	inline constexpr Matrix4 Matrix4::calculateTranspose(const Matrix4& matrix)
	{
		return Matrix4(
			matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], matrix.m[3][0],
			matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], matrix.m[3][1],
			matrix.m[0][2], matrix.m[1][2], matrix.m[2][2], matrix.m[3][2],
			matrix.m[0][3], matrix.m[1][3], matrix.m[2][3], matrix.m[3][3]
		);
	}
	// 2�̍s��̑Ή�����l�̊Ԃ���`��Ԃ��܂�
	inline Matrix4 Matrix4::lerp(const Matrix4& value1, const Matrix4& value2, float amount)
	{
		Vector3		scale = Vector3::lerp(value1.calculateScale(), value2.calculateScale(), amount);
		Quaternion  rotate = Quaternion::slerp(value1.calculateRotation(), value2.calculateRotation(), amount);
		Vector3		translation = Vector3::lerp(value1.calculateTranslation(), value2.calculateTranslation(), amount);

		return Matrix4::createTRS(translation, rotate, scale);
	}
	// ��]�s��𐳋K�����܂�
	inline constexpr Matrix4 Matrix4::normalizeRotationMatrix(const Matrix4& matrix)
	{
		Matrix4 result = matrix;

		Vector3 f(result.m[2][0], result.m[2][1], result.m[2][2]);
		Vector3 u(result.m[1][0], result.m[1][1], result.m[1][2]);
		Vector3 l(Vector3::normalize(Vector3::cross(u, f)));

		u = Vector3::normalize(Vector3::cross(f, l));
		f = Vector3::cross(l, u);

		result.m[0][0] = l.x; result.m[0][1] = l.y; result.m[0][2] = l.z;
		result.m[1][0] = u.x; result.m[1][1] = u.y; result.m[1][2] = u.z;
		result.m[2][0] = f.x; result.m[2][1] = f.y; result.m[2][2] = f.z;

		return result;
	}
	// �X�N���[�����W�n�ɕϊ�����s��𐶐�
	inline constexpr Matrix4 Matrix4::createScreen(float x, float y, float width, float height)
	{
		float w = width / 2.0f;
		float h = height / 2.0f;

		return Matrix4(
				w,  0.0f, 0.0f, 0.0f,
			 0.0f,    -h, 0.0f, 0.0f,
			 0.0f,  0.0f, 1.0f, 0.0f,
			w + x, h + y, 0.0f, 1.0f
		);
	}
	// ������W�n�̃r���[�s��𐶐��iDirectX���j
	inline constexpr Matrix4 Matrix4::createLookAtLH(const Vector3& position, const Vector3& target, const Vector3& up)
	{
		Vector3 z = Vector3::normalize(target - position);
		Vector3 x = Vector3::normalize(Vector3::cross(up, z));
		Vector3 y = Vector3::cross(z, x);

		return Matrix4(
			x.x, y.x, z.x, 0.0f,
			x.y, y.y, z.y, 0.0f,
			x.z, y.z, z.z, 0.0f,
			-Vector3::dot(position, x), -Vector3::dot(position, y), -Vector3::dot(position, z), 1.0f
		);
	}
	// �E����W�n�̃r���[�s��𐶐��iOpenGL���j
	inline constexpr Matrix4 Matrix4::createLookAtRH(const Vector3& position, const Vector3& target, const Vector3& up)
	{
		Vector3 z = Vector3::normalize(position - target);
		Vector3 x = Vector3::normalize(Vector3::cross(up, z));
		Vector3 y = Vector3::cross(z, x);
		return Matrix4(
			x.x, y.x, z.x, 0.0f,
			x.y, y.y, z.y, 0.0f,
			x.z, y.z, z.z, 0.0f,
			-Vector3::dot(position, x), -Vector3::dot(position, y), -Vector3::dot(position, z), 1.0f
		);
	}

	// ������W�n�̕��s���e�s��𐶐��iDirectX���j
	inline constexpr Matrix4 Matrix4::createOrthographicLH(float width, float height, float zn, float zf)
	{
		return Matrix4(
			2 / width,	0.0f,		0.0f,			0.0f,
			0.0f,		2 / height, 0.0f,			0.0f,
			0.0f,		0.0f,		1 / (zf - zn),	0.0f,
			0.0f,		0.0f,		zn / (zn - zf), 1.0f
		);
	}

	// ������W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iDirectX���j
	inline constexpr Matrix4 Matrix4::createPerspectiveFieldOfViewLH(float fov, float aspect, float zn, float zf)
	{
		float h = 1.0f / helper::tan(fov / 2.0f);
		float w = h / aspect;

		return Matrix4(
			w,    0.0f,                   0.0f, 0.0f,
			0.0f,    h,                   0.0f, 0.0f,
			0.0f, 0.0f,         zf / (zf - zn), 1.0f,
			0.0f, 0.0f, (-zn * zf) / (zf - zn), 0.0f
		);
	}
	// �E����W�n�̃p�[�X�y�N�e�B�u�ˉe�s��𐶐��iOpenGL���j
	inline constexpr Matrix4 Matrix4::createPerspectiveFieldOfViewRH(float fov, float aspect, float zn, float zf)
	{
		float ys = 1.0f / helper::tan(fov / 2.0f);
		float xs = ys / aspect;

		return Matrix4(
			  xs, 0.0f,                     0.0f,  0.0f,
			0.0f,  ys,                      0.0f,  0.0f,
			0.0f, 0.0f,    (zf + zn) / (zn - zf), -1.0f,
			0.0f, 0.0f, (2.0f*zf*zn) / (zn - zf),  0.0f
		);
	}
	// �w�肳�ꂽ Matrix �ɂ���āAVector3���g�����X�t�H�[�����܂�
	inline constexpr Vector3 Matrix4::transformVec(const Vector3& position, const Matrix4& matrix)
	{
		float w = position.x * matrix.m[0][3] + position.y * matrix.m[1][3] + position.z * matrix.m[2][3] + matrix.m[3][3];
		return Vector3(
			(position.x * matrix.m[0][0] + position.y * matrix.m[1][0] + position.z * matrix.m[2][0] + matrix.m[3][0]) / w,
			(position.x * matrix.m[0][1] + position.y * matrix.m[1][1] + position.z * matrix.m[2][1] + matrix.m[3][1]) / w,
			(position.x * matrix.m[0][2] + position.y * matrix.m[1][2] + position.z * matrix.m[2][2] + matrix.m[3][2]) / w
		);
	}
	// �w�肳�ꂽ Matrix �ɂ���āA�@���x�N�g�����g�����X�t�H�[�����܂�
	inline constexpr Vector3 Matrix4::transformVecNormal(const Vector3& position, const Matrix4& matrix)
	{
		return Vector3(
			position.x * matrix.m[0][0] + position.y * matrix.m[1][0] + position.z * matrix.m[2][0],
			position.x * matrix.m[0][1] + position.y * matrix.m[1][1] + position.z * matrix.m[2][1],
			position.x * matrix.m[0][2] + position.y * matrix.m[1][2] + position.z * matrix.m[2][2]
		);
	}
	// �ړ��̒l���Đݒ�
	inline constexpr void Matrix4::setTranslation(const Vector3& translation)
	{
		m[3][0] = translation.x;
		m[3][1] = translation.y;
		m[3][2] = translation.z;
	}
	// �ړ��A��]�A�X�P�[���̒l���Đݒ�
	inline constexpr void Matrix4::setTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale)
	{
		Matrix4 result = createTRS(translation, rotate, scale);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = result.m[i][j];
			}
		}
	}
	// ���W���v�Z
	inline constexpr Vector3 Matrix4::calculateTranslation() const
	{
		return Vector3(m[3][0], m[3][1], m[3][2]);
	}
	// ��]���v�Z
	inline constexpr Quaternion Matrix4::calculateRotation() const
	{
		Quaternion result;

		Matrix4 matrix = normalizeRotationMatrix(*this);

		float tr = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2] + 1.0f;

		if (tr >= 1.0f)
		{
			float fourD = 2.0f * helper::sqrt(tr);

			result.x = (matrix.m[1][2] - matrix.m[2][1]) / fourD;
			result.y = (matrix.m[2][0] - matrix.m[0][2]) / fourD;
			result.z = (matrix.m[0][1] - matrix.m[1][0]) / fourD;
			result.w = fourD / 4.0f;

			return result;
		}

		int i = 0;

		if (matrix.m[0][0] <= matrix.m[1][1])
		{
			i = 1;
		}

		if (matrix.m[2][2] > matrix.m[i][i])
		{
			i = 2;
		}

		int j = (i + 1) % 3;
		int k = (j + 1) % 3;

		tr = matrix.m[i][i] - matrix.m[j][j] - matrix.m[k][k] + 1.0f;

		float fourD = 2.0f * helper::sqrt(tr);

		result[i] = fourD / 4.0f;
		result[j] = (matrix.m[j][i] + matrix.m[i][j]) / fourD;
		result[k] = (matrix.m[k][i] + matrix.m[i][k]) / fourD;
		result[3] = (matrix.m[j][k] - matrix.m[k][j]) / fourD;

		return result;
	}
	// �X�P�[���l���v�Z
	inline constexpr Vector3 Matrix4::calculateScale() const
	{
		return Vector3(
			Vector3(m[0][0], m[0][1], m[0][2]).length(),
			Vector3(m[1][0], m[1][1], m[1][2]).length(),
			Vector3(m[2][0], m[2][1], m[2][2]).length()
		);
	}
	// ������W�n�̑O���x�N�g�����v�Z�iDirectX���j
	inline constexpr Vector3 Matrix4::calculateForwardLH() const
	{
		return Vector3::normalize(Vector3(m[2][0], m[2][1], m[2][2]));
	}
	// �E����W�n�̑O���x�N�g�����v�Z�iOpenGL���j
	inline constexpr Vector3 Matrix4::calculateForwardRH() const
	{
		return Vector3::normalize(Vector3(m[2][0], m[2][1], -m[2][2]));
	}
	// ����x�N�g�����v�Z
	inline constexpr Vector3 Matrix4::calculateUp() const
	{
		return Vector3::normalize(Vector3(m[1][0], m[1][1], m[1][2]));
	}
	// �E�x�N�g�����v�Z
	inline constexpr Vector3 Matrix4::calculateRight() const
	{
		return Vector3::normalize(Vector3(m[0][0], m[0][1], m[0][2]));
	}
	// �t�s����v�Z
	inline constexpr Matrix4 Matrix4::calculateInvert() const
	{
		return calculateInvert(*this);
	}
	// �]�u�s����v�Z
	inline constexpr Matrix4 Matrix4::calculateTranspose() const
	{
		return calculateTranspose(*this);
	}
	// ���W�ϊ��i�ʏ�j
	inline constexpr Vector3 Matrix4::multiplyPoint(const Vector3& point)
	{
		float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
		float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
		float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
		float w = point.x * m[0][3] + point.y * m[1][3] + point.z * m[2][3] + m[3][3];
		return Vector3{ x / w, y / w, z / w };
	}
	inline constexpr Vector3 Matrix4::multiplyPointFast(const Vector3& point)
	{
		float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
		float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
		float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
		return Vector3{ x, y, z };
	}
	// �x�N�g���ϊ��i���s�ړ������j
	inline constexpr Vector3 Matrix4::multiplyVector(const Vector3& vector)
	{
		float x = vector.x * m[0][0] + vector.y * m[1][0] + vector.z * m[2][0];
		float y = vector.x * m[0][1] + vector.y * m[1][1] + vector.z * m[2][1];
		float z = vector.x * m[0][2] + vector.y * m[1][2] + vector.z * m[2][2];
		return Vector3{ x, y, z };
	}
	constexpr Matrix4 operator - (const Matrix4& m)
	{
		return Matrix4(
			-m.m[0][0], -m.m[0][1], -m.m[0][2], -m.m[0][3],
			-m.m[1][0], -m.m[1][1], -m.m[1][2], -m.m[1][3],
			-m.m[2][0], -m.m[2][1], -m.m[2][2], -m.m[2][3],
			-m.m[3][0], -m.m[3][1], -m.m[3][2], -m.m[3][3]);
	}
	constexpr Matrix4& operator += (Matrix4& m1, const Matrix4& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m1.m[i][j] += m2.m[i][j];
			}
		}
		return m1;
	}
	constexpr Matrix4& operator -= (Matrix4& m1, const Matrix4& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m1.m[i][j] -= m2.m[i][j];
			}
		}
		return m1;
	}
	constexpr Matrix4& operator *= (Matrix4& m1, const Matrix4& m2)
	{
		Matrix4 result = mat4Zero;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; ++k)
				{
					result.m[i][j] += m1.m[i][k] * m2.m[k][j];
				}
			}
		}
		m1 = result;
		return m1;
	}
	constexpr Matrix4& operator *= (Matrix4& m, float s)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m.m[i][j] *= s;
			}
		}
		return m;
	}
	constexpr Matrix4& operator /= (Matrix4& m, float s)
	{
		return m *= (1.0f / s);
	}
	constexpr Matrix4 operator * (Matrix4 m1, const Matrix4& m2)
	{
		return m1 *= m2;
	}
	constexpr Matrix4 operator + (Matrix4 m1, const Matrix4& m2)
	{
		return m1 += m2;
	}
	constexpr Matrix4 operator - (Matrix4 m1, const Matrix4& m2)
	{
		return m1 -= m2;
	}
	constexpr Matrix4 operator*(Matrix4 m, float s)
	{
		return m *= s;
	}
	constexpr Matrix4 operator*(float s, Matrix4 m)
	{
		return m *= s;
	}
	constexpr Matrix4 operator/(Matrix4 m, float s)
	{
		return m /= s;
	}
	constexpr Vector3 operator * (const Vector3& v, const Matrix4& m)
	{
		return Matrix4::transformVec(v, m);
	}
}
#endif // !MATRIX_4_H_