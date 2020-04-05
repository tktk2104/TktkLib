#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <string>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include "../MathHelper.h"
#include "Vector3.h"

namespace tktkMath
{
	// �R������]��\���N�I�[�^�j�I���̍\����
	struct Quaternion
	{
	public:

		// �R���X�g���N�^
		constexpr Quaternion() = default;
		constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	public:

		// �C���f�b�N�X�Ŋe�v�f�ɃA�N�Z�X���邽�߂̃I�[�o�[���[�h
		constexpr float operator[](int index) const;
		constexpr float& operator[](int index);

	public:

		// �I�C���[�p����N�I�[�^�j�I���𐶐�����
		constexpr static Quaternion createFromEulerAngle(const Vector3& euler);
		// axis�̎���� degree �x������]����N�I�[�^�j�I���𐶐�����
		constexpr static Quaternion createFromAxisAngle(const Vector3& axis, float degree);
		// from����to�ւ̉�]�����߂�
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion createFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// �w�肵����������������]�����߂�
		constexpr static Quaternion createLookRotation(const Vector3& view, const Vector3& up = vec3Up);
		// from����to�ւ̉�]�����߂�
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion createRotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);
		// �t�N�I�[�^�j�I�����v�Z����
		constexpr static Quaternion calculateInvert(const Quaternion& rotation);
		// �Q�̉�] a �� b �Ԃ̊p�x���v�Z����
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static float calculateAngle(const Quaternion& q1, const Quaternion& q2);
		// ���ς��v�Z����
		constexpr static float calculateDot(const Quaternion& q1, const Quaternion& q2);
		// ���K������
		constexpr static Quaternion normalize(const Quaternion& q);
		// a��b�̊Ԃ�t�Ő��`��Ԃ���it��0��1�̊ԂŃN�����v����j
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion lerp(const Quaternion& value1, const Quaternion& value2, float t);
		// a��b�̊Ԃ�t�Ő��`��Ԃ���
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion lerpUnclamped(const Quaternion& value1, const Quaternion& value2, float t);
		// ���ʐ��`���
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion slerp(const Quaternion& value1, const Quaternion& value2, float amount);
		// ���ʐ��`���
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		static Quaternion slerpUnclamped(const Quaternion& value1, const Quaternion& value2, float amount);

	private:

		// 0�`360�̃v���X�̊p�x�ɕϊ�
		constexpr static Vector3 internalMakePositive(Vector3 euler);

	public:
		
		// �N�I�[�^�j�I���̃m�������v�Z����
		constexpr float calculateLength() const;
		// �I�C���[�p���v�Z����
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		Vector3 calculateEulerAngle() const;
		// �e�v�f���Đݒ肷��
		constexpr void setValue(float x, float y, float z, float w);
		// from����to�ւ̉�]�����g�ɐݒ肷��
		// TODO : �R���p�C�����萔�֐��ɑΉ�����
		void setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// �w�肵����������������]�����g�ɐݒ肷��
		constexpr void setLookRotation(const Vector3& view, const Vector3& up = vec3Up);
		// �Q�̉�]����̓�����������^��Ԃ�
		constexpr bool equals(const Quaternion& other) const;

		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		// �e�v�f
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
		float w{ 0.0f };
	};

	// �N�I�[�^�j�I�����g����vec3�ɕύX��������֐��B
	struct Vector3UseQuaternionEditor
	{
		// ���݂̈ʒu current ���� target �Ɍ����ăx�N�g������]���܂�
		constexpr static Vector3 rotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
		// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		constexpr static Vector3 slerp(const Vector3& value1, const Vector3& value2, float amount);
		// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		constexpr static Vector3 slerpUnclamped(const Vector3& value1, const Vector3& value2, float amount);
	};

	// �萔�B
	constexpr Quaternion identity = { 0.0f, 0.0f, 0.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	constexpr Quaternion	operator -  (const Quaternion& q);
	constexpr Quaternion&	operator += (Quaternion& q1, const Quaternion& q2);
	constexpr Quaternion&	operator -= (Quaternion& q1, const Quaternion& q2);
	constexpr Quaternion&	operator *= (Quaternion& q, float s);
	constexpr Quaternion&	operator /= (Quaternion& q, float s);
	constexpr Quaternion&	operator *= (Quaternion& q1, const Quaternion& q2);
	constexpr Quaternion	operator +  (Quaternion q1, const Quaternion& q2);
	constexpr Quaternion	operator -  (Quaternion q1, const Quaternion& q2);
	constexpr Quaternion	operator *  (Quaternion q1, const Quaternion& q2);
	constexpr Quaternion	operator *  (Quaternion q, float s);
	constexpr Quaternion	operator *  (float s, Quaternion q);
	constexpr Quaternion	operator /  (Quaternion q, float s);
	constexpr Vector3		operator *  (const Quaternion& rotation, const Vector3& point);
	std::ostream&			operator << (std::ostream& os, const Quaternion& quaternion);

//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	inline constexpr float Quaternion::operator[](int index) const
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		case 3: return w; break;
		}
		throw std::runtime_error("quaternion operator[] out of range");
	}
	inline constexpr float& Quaternion::operator[](int index)
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		case 3: return w; break;
		}
		throw std::runtime_error("quaternion operator[] out of range");
	}
	// �I�C���[�p����N�I�[�^�j�I���𐶐�����
	inline constexpr Quaternion Quaternion::createFromEulerAngle(const Vector3& euler)
	{
		Vector3 v = Vector3(
			helper::toRadians(euler.x),
			helper::toRadians(euler.y),
			helper::toRadians(euler.z)
		);

		float c1 = helper::cos(v.x * 0.5f);
		float c2 = helper::cos(v.y * 0.5f);
		float c3 = helper::cos(v.z * 0.5f);
		float s1 = helper::sin(v.x * 0.5f);
		float s2 = helper::sin(v.y * 0.5f);
		float s3 = helper::sin(v.z * 0.5f);

		float result_x = s1 * c2 * c3 + c1 * s2 * s3;
		float result_y = c1 * s2 * c3 - s1 * c2 * s3;
		float result_z = c1 * c2 * s3 - s1 * s2 * c3;
		float result_w = c1 * c2 * c3 + s1 * s2 * s3;

		return Quaternion(result_x, result_y, result_z, result_w);
	}
	// axis�̎���� degree �x������]����N�I�[�^�j�I���𐶐�����
	inline constexpr Quaternion Quaternion::createFromAxisAngle(const Vector3& axis, float degree)
	{
		float sin = helper::sin(degree / 2.0f);

		return Quaternion(
			sin * axis.x,
			sin * axis.y,
			sin * axis.z,
			helper::cos(degree / 2.0f)
		);
	}
	// from����to�ւ̉�]�����߂�
	inline Quaternion Quaternion::createFromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
	{
		float angle = Vector3::angle(fromDirection, toDirection);

		if (angle < helper::kEpsilon)
		{
			return identity;
		}

		Vector3 axis = Vector3::cross(fromDirection, toDirection);

		if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			axis = Vector3::cross(vec3ForwardLH, fromDirection);

			if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
			{
				axis = Vector3::cross(vec3Right, fromDirection);
			}
		}
		return createFromAxisAngle(axis, angle);
	}
	// �w�肵����������������]�����߂�
	inline constexpr Quaternion Quaternion::createLookRotation(const Vector3& view, const Vector3& up)
	{
		Vector3 forward = Vector3::normalize(view);

		if (forward.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			forward = vec3ForwardLH;
		}

		Vector3 right = Vector3::cross(up, forward);

		if (right.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			right = vec3Right;
		}

		Vector3 upward = Vector3::cross(forward, right);
		upward = Vector3::normalize(upward);

		right = Vector3::cross(upward, forward);

		Quaternion result;

		float radicand = right.x + upward.y + forward.z;

		if (radicand > 0.0f)
		{
			result.w = std::sqrt(1.0f + radicand) * 0.5f;
			float recip = 1.0f / (4.0f * result.w);
			result.x = (upward.z - forward.y) * recip;
			result.z = (forward.x - right.z) * recip;
			result.y = (right.y - upward.x) * recip;
		}
		else if (right.x >= upward.y && right.x >= forward.z)
		{
			result.x = std::sqrt(1.0f + right.x + upward.y - forward.z) * 0.5f;
			float recip = 1.0f / (4.0f * result.x);
			result.w = (upward.z - forward.y) * recip;
			result.z = (forward.x + right.z) * recip;
			result.y = (right.y + upward.z) * recip;
		}
		else if (upward.y > forward.z)
		{
			result.y = std::sqrt(1.0f - right.x + upward.y - forward.z) * 0.5f;
			float recip = 1.0f / (4.0f * result.y);
			result.z = (upward.z + forward.y) * recip;
			result.w = (forward.x - right.z) * recip;
			result.x = (right.y + upward.x) * recip;
		}
		else
		{
			result.z = std::sqrt(1.0f - right.x - upward.y + forward.z) * 0.5f;
			float recip = 1.0f / (4.0f * result.z);
			result.y = (upward.z + forward.y) * recip;
			result.x = (forward.x + right.z) * recip;
			result.w = (right.y - upward.x) * recip;
		}
		return result;
	}
	// from����to�ւ̉�]�����߂�
	inline Quaternion Quaternion::createRotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta)
	{
		Vector3 eulerFrom = from.calculateEulerAngle();

		Vector3 eulerTo = to.calculateEulerAngle();

		Vector3 rotatedEuler = Vector3UseQuaternionEditor::rotateTowards(eulerFrom, eulerTo, maxDegreesDelta, 0.0f);

		return Quaternion::createFromEulerAngle(rotatedEuler);
	}
	// �t�N�I�[�^�j�I�����v�Z����
	inline constexpr Quaternion Quaternion::calculateInvert(const Quaternion& rotation)
	{
		return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
	}
	// �Q�̉�] a �� b �Ԃ̊p�x���v�Z����
	inline float Quaternion::calculateAngle(const Quaternion& q1, const Quaternion& q2)
	{
		float afterDot = calculateDot(q1, q2);

		if (afterDot > 1.0f - helper::kEpsilon) return 0.0f;

		return helper::acos(std::min(helper::abs(afterDot), 1.0f)) * 2.0f;
	}
	// ���ς��v�Z����
	inline constexpr float Quaternion::calculateDot(const Quaternion& q1, const Quaternion& q2)
	{
		return (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);
	}
	// ���K������
	inline constexpr Quaternion Quaternion::normalize(const Quaternion& q)
	{
		float len = q.calculateLength();

		if (len > helper::kEpsilon)
		{
			return Quaternion(q) / len;
		}
		return Quaternion(q);
	}
	// a��b�̊Ԃ�t�Ő��`��Ԃ���it��0��1�̊ԂŃN�����v����j
	inline Quaternion Quaternion::lerp(const Quaternion& value1, const Quaternion& value2, float t)
	{
		Vector3 eulerValue1 = value1.calculateEulerAngle();
		Vector3 eulerValue2 = value2.calculateEulerAngle();

		Vector3 afterLerp = Vector3::lerp(eulerValue1, eulerValue2, t);

		return Quaternion::createFromEulerAngle(afterLerp);
	}
	// a��b�̊Ԃ�t�Ő��`��Ԃ���
	inline Quaternion Quaternion::lerpUnclamped(const Quaternion& value1, const Quaternion& value2, float t)
	{
		Vector3 eulerValue1 = value1.calculateEulerAngle();
		Vector3 eulerValue2 = value2.calculateEulerAngle();

		Vector3 afterLerp = Vector3::lerpUnclamped(eulerValue1, eulerValue2, t);

		return Quaternion::createFromEulerAngle(afterLerp);
	}
	// ���ʐ��`���
	inline Quaternion Quaternion::slerp(const Quaternion& value1, const Quaternion& value2, float amount)
	{
		return slerpUnclamped(value1, value2, helper::clamp(amount, 0.0f, 1.0f));
	}
	// ���ʐ��`���
	inline Quaternion Quaternion::slerpUnclamped(const Quaternion& value1, const Quaternion& value2, float amount)
	{
		float cos = calculateDot(value1, value2);

		float sign = 1.0f;

		if (cos < 0.0f)
		{
			cos = -cos;
			sign = -1.0f;
		}

		float t0 = 1.0f - amount;
		float t1 = amount;

		if (cos < 0.999f)
		{
			float theta = helper::acos(cos);
			t0 = helper::sin(theta * t0) / helper::sin(theta);
			t1 = helper::sin(theta * t1) / helper::sin(theta);
		}
		return Quaternion::normalize(((value1 * t0) + (value2 * sign * t1)));
	}
	// 0�`360�̃v���X�̊p�x�ɕϊ�
	inline constexpr Vector3 Quaternion::internalMakePositive(Vector3 euler)
	{
		constexpr float negativeFlip = helper::toDegrees(-0.0001f);
		constexpr float positiveFlip = 360.0f + negativeFlip;

		if (euler.x < negativeFlip)
			euler.x += 360.0f;
		else if (euler.x > positiveFlip)
			euler.x -= 360.0f;

		if (euler.y < negativeFlip)
			euler.y += 360.0f;
		else if (euler.y > positiveFlip)
			euler.y -= 360.0f;

		if (euler.z < negativeFlip)
			euler.z += 360.0f;
		else if (euler.z > positiveFlip)
			euler.z -= 360.0f;

		return euler;
	}
	// �N�I�[�^�j�I���̃m�������v�Z����
	inline constexpr float Quaternion::calculateLength() const
	{
		return helper::sqrt(calculateDot(*this, *this));
	}
	// �I�C���[�p���v�Z����
	inline Vector3 Quaternion::calculateEulerAngle() const
	{
		Vector3 ax = *this * Vector3{ 1.0f, 0.0f, 0.0f };
		Vector3 ay = *this * Vector3{ 0.0f, 1.0f, 0.0f };
		Vector3 az = *this * Vector3{ 0.0f, 0.0f, 1.0f };
		Vector3 result = Vector3(0.0f, 0.0f, 0.0f);
		if (az.y < 1.0f) {
			if (az.y > -1.0f) {
				result.x = helper::asin(-az.y);
				result.y = helper::atan(az.x, az.z);
				result.z = helper::atan(ax.y, ay.y);
			}
			else {
				// Not a unique solution.
				result.x = helper::pi / 2.0f;
				result.y = -helper::atan(-ay.x, ax.x);
				result.z = 0.0f;
			}
		}
		else {
			// Not a unique solution.
			result.x = -helper::pi / 2.0f;
			result.y = helper::atan(-ay.x, ax.x);
			result.z = 0.0f;
		}
		return internalMakePositive(Vector3(
			helper::toDegrees(result.x),
			helper::toDegrees(result.y),
			helper::toDegrees(result.z)
		));
	}
	// �e�v�f���Đݒ肷��
	inline constexpr void Quaternion::setValue(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	// from����to�ւ̉�]�����g�ɐݒ肷��
	inline void Quaternion::setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
	{
		*this = createFromToRotation(fromDirection, toDirection);
	}
	// �w�肵����������������]�����g�ɐݒ肷��
	inline constexpr void Quaternion::setLookRotation(const Vector3& view, const Vector3& up)
	{
		*this = createLookRotation(view, up);
	}
	// �Q�̉�]����̓�����������^��Ԃ�
	inline constexpr bool Quaternion::equals(const Quaternion& other) const
	{
		return (
			helper::abs(x - other.x) < helper::kEpsilon &&
			helper::abs(y - other.y) < helper::kEpsilon &&
			helper::abs(z - other.z) < helper::kEpsilon &&
			helper::abs(w - other.w) < helper::kEpsilon
			);
	}
	constexpr Quaternion operator - (const Quaternion& q)
	{
		return Quaternion(-q.x, -q.y, -q.z, -q.w);
	}
	constexpr Quaternion& operator += (Quaternion& q1, const Quaternion& q2)
	{
		q1.x += q2.x;
		q1.y += q2.y;
		q1.z += q2.z;
		q1.w += q2.w;
		return q1;
	}
	constexpr Quaternion& operator -= (Quaternion& q1, const Quaternion& q2)
	{
		q1.x -= q2.x;
		q1.y -= q2.y;
		q1.z -= q2.z;
		q1.w -= q2.w;
		return q1;
	}
	constexpr Quaternion& operator *= (Quaternion& q, float s)
	{
		q.x *= s;
		q.y *= s;
		q.z *= s;
		q.w *= s;
		return q;
	}
	constexpr Quaternion& operator /= (Quaternion& q, float s)
	{
		q.x /= s;
		q.y /= s;
		q.z /= s;
		q.w /= s;
		return q;
	}
	constexpr Quaternion& operator *= (Quaternion& q1, const Quaternion& q2)
	{
		q1 = Quaternion(
			q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
			-q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
			q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
			-q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w);
		return q1;
	}
	constexpr Quaternion operator + (Quaternion q1, const Quaternion& q2)
	{
		return q1 += q2;
	}
	constexpr Quaternion operator - (Quaternion q1, const Quaternion& q2)
	{
		return q1 -= q2;
	}
	constexpr Quaternion operator * (Quaternion q1, const Quaternion& q2)
	{
		return q1 *= q2;
	}
	constexpr Quaternion operator * (Quaternion q, float s)
	{
		return q *= s;
	}
	constexpr Quaternion operator * (float s, Quaternion q)
	{
		return q *= s;
	}
	constexpr Quaternion operator / (Quaternion q, float s)
	{
		return q /= s;
	}
	constexpr Vector3 operator*(const Quaternion& rotation, const Vector3& point)
	{
		float x = rotation.x * 2.0f;
		float y = rotation.y * 2.0f;
		float z = rotation.z * 2.0f;

		float xx = rotation.x * x;
		float yy = rotation.y * y;
		float zz = rotation.z * z;

		float xy = rotation.x * y;
		float xz = rotation.x * z;
		float yz = rotation.y * z;

		float wx = rotation.w * x;
		float wy = rotation.w * y;
		float wz = rotation.w * z;

		Vector3 result;

		result.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
		result.y = (xy + wz) * point.x + (1.0f - (xx - zz)) * point.y + (yz - wx) * point.z;
		result.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;

		return result;
	}
	// ���݂̈ʒu current ���� target �Ɍ����ăx�N�g������]���܂�
	inline constexpr Vector3 Vector3UseQuaternionEditor::rotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta)
	{
		float curLength = current.length();
		float targetLength = target.length();

		if (curLength * targetLength < helper::kEpsilon)
		{
			return Vector3::moveTowards(current, target, maxMagnitudeDelta);
		}

		Vector3 afterNormalizeCurrent = current / curLength;
		Vector3 afterNormalizeTarget = target / targetLength;

		float angleRad = helper::toRadians(Vector3::angle(afterNormalizeCurrent, afterNormalizeTarget));

		Vector3 axis = Vector3::cross(afterNormalizeCurrent, afterNormalizeTarget);

		if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			axis = Vector3::cross(vec3ForwardLH, afterNormalizeCurrent);

			if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
			{
				axis = Vector3::cross(vec3Right, afterNormalizeCurrent);
			}
		}

		float angleTowards = helper::moveTowards(0.0f, angleRad, maxRadiansDelta);

		float lengthTowards = helper::moveTowards(curLength, targetLength, maxMagnitudeDelta);

		return Quaternion::createFromAxisAngle(axis, helper::toDegrees(angleTowards)) * current * lengthTowards;
	}
	// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
	inline constexpr Vector3 Vector3UseQuaternionEditor::slerp(const Vector3& value1, const Vector3& value2, float amount)
	{
		float value1Length = value1.length();
		float value2Length = value2.length();

		if (value1Length * value2Length < helper::kEpsilon)
		{
			return Vector3::lerp(value1, value2, amount);
		}

		Vector3 afterNormalizeValue1 = value1 / value1Length;
		Vector3 afterNormalizeValue2 = value2 / value2Length;

		float angle = Vector3::angle(afterNormalizeValue1, afterNormalizeValue2);

		Vector3 axis = Vector3::cross(afterNormalizeValue1, afterNormalizeValue2);

		if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			axis = Vector3::cross(vec3Right, afterNormalizeValue1);
		}

		return Quaternion::createFromAxisAngle(axis, angle * amount) * afterNormalizeValue1 * helper::lerp(value1Length, value2Length, amount);
	}
	// ����� 2 �̃x�N�g���Ԃ��Ԃ��܂�
	inline constexpr Vector3 Vector3UseQuaternionEditor::slerpUnclamped(const Vector3& value1, const Vector3& value2, float amount)
	{
		float value1Length = value1.length();
		float value2Length = value2.length();

		if (value1Length * value2Length < helper::kEpsilon)
		{
			return Vector3::lerp(value1, value2, amount);
		}

		Vector3 afterNormalizeValue1 = value1 / value1Length;
		Vector3 afterNormalizeValue2 = value2 / value2Length;

		float angle = Vector3::angle(afterNormalizeValue1, afterNormalizeValue2);

		Vector3 axis = Vector3::cross(afterNormalizeValue1, afterNormalizeValue2);

		if (axis.lengthSquared() < (helper::kEpsilon * helper::kEpsilon))
		{
			axis = Vector3::cross(vec3Right, afterNormalizeValue1);
		}

		return Quaternion::createFromAxisAngle(axis, angle * amount) * afterNormalizeValue1 * helper::lerpUnclamped(value1Length, value2Length, amount);
	}
}
#endif // !QUATERNION_H_