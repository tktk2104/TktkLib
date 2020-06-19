#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <limits>
#include <string>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include "../ConstexprMathHelper.h"

namespace tktkConstexprMath
{
	// 2�������W�E�x�N�g���̍\����
	struct Vector2
	{
	public:

		// �R���X�g���N�^
		constexpr Vector2() = default;
		constexpr Vector2(float value)		: x(value), y(value) {}
		constexpr Vector2(float x, float y) : x(x), y(y) {}

	public:

		// �C���f�b�N�X�Ŋe�v�f�ɃA�N�Z�X���邽�߂̃I�[�o�[���[�h
		constexpr float  operator[](int index) const;
		constexpr float& operator[](int index);

	public:

		// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
		static constexpr Vector2 normalize(const Vector2& value);
		// 2�̃x�N�g���̂Ȃ��p��Ԃ�
		static constexpr float angle(const Vector2& vector1, const Vector2& vector2);
		// �Q�̃x�N�g���̊Ԃ̊p�x���擾
		static constexpr float signedAngle(const Vector2& vector1, const Vector2& vector2);
		// 2�̃x�N�g���̓��ς��v�Z���܂�
		static constexpr float dot(const Vector2& vector1, const Vector2& vector2);
		// 2�̃x�N�g���̊O�ς��v�Z���܂�
		static constexpr float cross(const Vector2& vector1, const Vector2& vector2);
		// 2�̃x�N�g���Ԃ̋������v�Z���܂�
		static constexpr float distance(const Vector2& vector1, const Vector2& vector2);
		// 2 �̒����x�N�g���Ԃ̋������v�Z���܂�
		static constexpr float distanceSquared(const Vector2& vector1, const Vector2& vector2);
		// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
		static constexpr Vector2 lerp(const Vector2& value1, const Vector2& value2, float amount);
		// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
		static constexpr Vector2 lerpUnclamped(const Vector2& value1, const Vector2& value2, float amount);
		// current����target�֌����Ĉړ����܂�
		static constexpr Vector2 moveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
		// current����target�֌����Ď��Ԃ̌o�߂ŏ��X�Ƀx�N�g����ω������܂�
		static constexpr Vector2 smoothDamp(const Vector2& current, const Vector2& target, Vector2* currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
		static constexpr Vector2 calculateMin(const Vector2& vector1, const Vector2& vector2);
		// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
		static constexpr Vector2 calculateMax(const Vector2& vector1, const Vector2& vector2);
		// �l���w�肳�ꂽ�͈͓��ɐ������܂�
		static constexpr Vector2 clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
		// �傫����maxLength�܂Ő��������l���擾���܂�
		static constexpr Vector2 clampLength(const Vector2& vector1, float maxLength);
		// �����̃x�N�g���̐��������̃x�N�g�����擾
		static constexpr Vector2 perpendicular(const Vector2& inDirection);
		// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾���܂�
		static constexpr Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
		// 2�̃x�N�g���̊e��������Z����
		static constexpr Vector2 scale(const Vector2& vector1, const Vector2& vector2);

	public:
		
		// �x�N�g���̒���
		constexpr float length() const;
		// �x�N�g���̒����̕���
		constexpr float lengthSquared() const;
		// �P�ʃx�N�g�����擾����
		constexpr Vector2 normalized() const;
		// ���g�ƈ����̒l����̓�����������^��Ԃ�
		constexpr bool equals(const Vector2& other);
		// �l���Đݒ肷��
		constexpr void setValue(float x, float y);

		// �x�N�g���̒l�𕶎���ɋN�����������擾
		std::string toString() const;

	public:

		// �e�v�f
		float x{ 0.0f };
		float y{ 0.0f };
	};

	// �萔�B
	constexpr Vector2 vec2Zero	= { 0.0f };
	constexpr Vector2 vec2One	= { 1.0f };
	constexpr Vector2 vec2Up	= { 0.0f,  1.0f };
	constexpr Vector2 vec2Down	= { 0.0f, -1.0f };
	constexpr Vector2 vec2Left	= { -1.0f,  0.0f };
	constexpr Vector2 vec2Right = { 1.0f,  0.0f };
	constexpr Vector2 vec2NegativeInfinity = { -std::numeric_limits<float>::infinity() };
	constexpr Vector2 vec2PositiveInfinity = {  std::numeric_limits<float>::infinity() };

	// ���Z�q�I�[�o�[���[�h�B
	constexpr Vector2	operator -  (const Vector2& v);
	constexpr Vector2&	operator += (Vector2& v1, const Vector2& v2);
	constexpr Vector2&	operator -= (Vector2& v1, const Vector2& v2);
	constexpr Vector2&	operator *= (Vector2& v, float s);
	constexpr Vector2&	operator /= (Vector2& v, float s);
	constexpr Vector2	operator +  (Vector2 v1, const Vector2& v2);
	constexpr Vector2	operator -  (Vector2 v1, const Vector2& v2);
	constexpr Vector2	operator *  (Vector2 v, float s);
	constexpr Vector2	operator *  (float s, Vector2 v);
	constexpr Vector2	operator /  (Vector2 v, float s);
	constexpr bool		operator == (const Vector2& lhs, const Vector2& rhs);
	constexpr bool		operator != (const Vector2& lhs, const Vector2& rhs);
	std::ostream&		operator << (std::ostream& os, const Vector2& vector2);

//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
	
	inline constexpr float Vector2::operator[](int index) const
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		}
		throw std::runtime_error("vector2 operator[] out of range");
	}
	inline constexpr float& Vector2::operator[](int index)
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		}
		throw std::runtime_error("vector2 operator[] out of range");
	}
	// �w��x�N�g������P�ʃx�N�g�����쐬���܂�
	inline constexpr Vector2 Vector2::normalize(const Vector2& value)
	{
		return Vector2(value).normalized();
	}
	// 2�̃x�N�g���̂Ȃ��p��Ԃ�
	inline constexpr float Vector2::angle(const Vector2& vector1, const Vector2& vector2)
	{
		float denominator = helper::sqrt(vector1.lengthSquared() * vector2.lengthSquared());

		if (denominator == 0.0f) return 0.0f;

		float dotValue = helper::clamp(dot(vector1, vector2) / denominator, -1.0f, 1.0f);

		return helper::acos(dotValue);
	}
	// �Q�̃x�N�g���̊Ԃ̊p�x���擾
	inline constexpr float Vector2::signedAngle(const Vector2& vector1, const Vector2& vector2)
	{
		float unSignedAngle = angle(vector1, vector2);

		// TODO : �B���ȕϐ����𒼂�
		float value = vector1.x * vector2.y - vector1.y * vector2.x;

		return unSignedAngle * helper::sign(value);
	}
	// 2�̃x�N�g���̓��ς��v�Z���܂�
	inline constexpr float Vector2::dot(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y);
	}
	// 2�̃x�N�g���̊O�ς��v�Z���܂�
	inline constexpr float Vector2::cross(const Vector2& vector1, const Vector2& vector2)
	{
		return  (vector1.x * vector2.y) - (vector1.y * vector2.x);
	}
	// 2�̃x�N�g���Ԃ̋������v�Z���܂�
	inline constexpr float Vector2::distance(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector2 - vector1).length();
	}
	// 2 �̒����x�N�g���Ԃ̋������v�Z���܂�
	inline constexpr float Vector2::distanceSquared(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector2 - vector1).lengthSquared();
	}
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	inline constexpr Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, float amount)
	{
		return Vector2(helper::lerp(value1.x, value2.x, amount), helper::lerp(value1.y, value2.y, amount));
	}
	// 2 �̃x�N�g���Ԃ̐��`��Ԃ��s���܂�
	inline constexpr Vector2 Vector2::lerpUnclamped(const Vector2& value1, const Vector2& value2, float amount)
	{
		return Vector2(helper::lerpUnclamped(value1.x, value2.x, amount), helper::lerpUnclamped(value1.y, value2.y, amount));
	}
	// current����target�֌����Ĉړ����܂�
	inline constexpr Vector2 Vector2::moveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
	{
		float toVectorX = target.x - current.x;
		float toVectorY = target.y - current.y;

		float sqDist = toVectorX * toVectorX * toVectorY * toVectorY;

		if (sqDist == 0 || (maxDistanceDelta >= 0 && sqDist <= maxDistanceDelta * maxDistanceDelta)) return target;

		float dist = helper::sqrt(sqDist);

		return Vector2(
			current.x + toVectorX / dist * maxDistanceDelta,
			current.y + toVectorY / dist * maxDistanceDelta
		);
	}
	// current����target�֌����Ď��Ԃ̌o�߂ŏ��X�Ƀx�N�g����ω������܂�
	inline constexpr Vector2 Vector2::smoothDamp(const Vector2& current, const Vector2& target, Vector2* currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		smoothTime = std::max(0.0001f, smoothTime);
		float omega = 2.0f / smoothTime;

		float x = omega * deltaTime;
		// TODO : ��̐����ɓ�̎�
		float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

		float changeX = current.x - target.x;
		float changeY = current.y - target.y;

		float maxChange = maxSpeed * smoothTime;

		float maxChangeSq = maxChange * maxChange;
		float sqDist = changeX * changeX + changeY * changeY;
		if (sqDist > maxChangeSq)
		{
			float mag = helper::sqrt(sqDist);
			changeX = changeX / mag * maxChange;
			changeY = changeY / mag * maxChange;
		}

		Vector2 afterCalcTarget = target;

		afterCalcTarget.x = current.x - changeX;
		afterCalcTarget.y = current.y - changeY;

		float tempX = (currentVelocity->x + omega * changeX) * deltaTime;
		float tempY = (currentVelocity->y + omega * changeY) * deltaTime;

		currentVelocity->x = (currentVelocity->x - omega * tempX) * exp;
		currentVelocity->y = (currentVelocity->y - omega * tempY) * exp;

		float outputX = afterCalcTarget.x + (changeX + tempX) * exp;
		float outputY = afterCalcTarget.y + (changeY + tempY) * exp;

		float origMinusCurrentX = target.x - current.x;
		float origMinusCurrentY = target.y - current.y;

		float outMinusOrigX = outputX - target.x;
		float outMinusOrigY = outputY - target.y;

		if (origMinusCurrentX * outMinusOrigX + origMinusCurrentY * outMinusOrigY > 0.0f)
		{
			outputX = target.x;
			outputY = target.y;

			currentVelocity->x = (outputX - target.x) / deltaTime;
			currentVelocity->y = (outputY - target.y) / deltaTime;
		}
		return Vector2(outputX, outputY);
	}
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރx�N�g����Ԃ��܂�
	inline constexpr Vector2 Vector2::calculateMin(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(std::min(vector1.x, vector2.x), std::min(vector1.y, vector2.y));
	}
	// ��v����e�����y�A�̍ł������l���܂ރx�N�g����Ԃ��܂�
	inline constexpr Vector2 Vector2::calculateMax(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(std::max(vector1.x, vector2.x), std::min(vector1.y, vector2.y));
	}
	// �l���w�肳�ꂽ�͈͓��ɐ������܂�
	inline constexpr Vector2 Vector2::clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
	{
		return Vector2(helper::clamp(value1.x, min.x, max.x), helper::clamp(value1.y, min.y, max.y));
	}
	// �傫����maxLength�܂Ő��������l���擾���܂�
	inline constexpr Vector2 Vector2::clampLength(const Vector2& vector1, float maxLength)
	{
		float sqrLength = vector1.lengthSquared();

		if (sqrLength > maxLength * maxLength)
		{
			float length = helper::sqrt(sqrLength);

			float normalizedX = vector1.x / length;
			float normalizedY = vector1.y / length;

			return Vector2(normalizedX * maxLength, normalizedY * maxLength);
		}
		return vector1;
	}
	// �����̃x�N�g���̐��������̃x�N�g�����擾
	inline constexpr Vector2 Vector2::perpendicular(const Vector2& inDirection)
	{
		return Vector2(-inDirection.y, inDirection.x);
	}
	// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾���܂�
	inline constexpr Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal)
	{
		float factor = -2.0f * dot(inNormal, inDirection);

		return Vector2(factor * inNormal.x + inDirection.x, factor * inNormal.y + inDirection.y);
	}
	// 2�̃x�N�g���̊e��������Z����
	inline constexpr Vector2 Vector2::scale(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(vector1.x * vector2.x, vector1.y * vector2.y);
	}
	// �x�N�g���̒���
	inline constexpr float Vector2::length() const
	{
		return helper::sqrt(dot(*this, *this));
	}
	// �x�N�g���̒����̕���
	inline constexpr float Vector2::lengthSquared() const
	{
		return dot(*this, *this);
	}
	// �P�ʃx�N�g�����擾����
	inline constexpr Vector2 Vector2::normalized() const
	{
		float len = length();

		if (len > helper::kEpsilon)
		{
			return Vector2(x / len, y / len);
		}
		return vec2Zero;
	}
	// ���g�ƈ����̒l����̓�����������^��Ԃ�
	inline constexpr bool Vector2::equals(const Vector2& other)
	{
		return (helper::equals(x, other.x) && helper::equals(y, other.y));
	}
	// �l���Đݒ肷��
	inline constexpr void Vector2::setValue(float x, float y)
	{
		Vector2::x = x;
		Vector2::y = y;
	}
	constexpr Vector2 operator - (const Vector2& v)
	{
		return Vector2(-v.x, -v.y);
	}
	constexpr Vector2& operator+=(Vector2& v1, const Vector2& v2)
	{
		v1.x += v2.x; v1.y += v2.y;
		return v1;
	}
	constexpr Vector2& operator-=(Vector2& v1, const Vector2& v2)
	{
		v1.x -= v2.x; v1.y -= v2.y;
		return v1;
	}
	constexpr Vector2& operator*=(Vector2& v, float s)
	{
		v.x *= s; v.y *= s;
		return v;
	}
	constexpr Vector2& operator/=(Vector2& v, float s)
	{
		v.x /= s; v.y /= s;
		return v;
	}
	constexpr Vector2 operator+(Vector2 v1, const Vector2& v2)
	{
		return v1 += v2;
	}
	constexpr Vector2 operator-(Vector2 v1, const Vector2& v2)
	{
		return v1 -= v2;
	}
	constexpr Vector2 operator*(Vector2 v, float s)
	{
		return v *= s;
	}
	constexpr Vector2 operator*(float s, Vector2 v)
	{
		return v *= s;
	}
	constexpr Vector2 operator/(Vector2 v, float s)
	{
		return v /= s;
	}
	constexpr bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
	}
	constexpr bool operator!=(const Vector2& lhs, const Vector2& rhs)
	{
		return !(lhs == rhs);
	}
}
#endif