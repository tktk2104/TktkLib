#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <limits>
#include <string>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include "../MathHelper.h"

namespace tktkMath
{
	// 2次元座標・ベクトルの構造体
	struct Vector2
	{
	public:

		// コンストラクタ
		constexpr Vector2() = default;
		constexpr Vector2(float value)		: x(value), y(value) {}
		constexpr Vector2(float x, float y) : x(x), y(y) {}

	public:

		// インデックスで各要素にアクセスするためのオーバーロード
		constexpr float  operator[](int index) const;
		constexpr float& operator[](int index);

	public:

		// 指定ベクトルから単位ベクトルを作成します
		static constexpr Vector2 normalize(const Vector2& value);
		// 2つのベクトルのなす角を返す
		static constexpr float angle(const Vector2& vector1, const Vector2& vector2);
		// ２つのベクトルの間の角度を取得
		static constexpr float signedAngle(const Vector2& vector1, const Vector2& vector2);
		// 2つのベクトルの内積を計算します
		static constexpr float dot(const Vector2& vector1, const Vector2& vector2);
		// 2つのベクトルの外積を計算します
		static constexpr float cross(const Vector2& vector1, const Vector2& vector2);
		// 2つのベクトル間の距離を計算します
		static constexpr float distance(const Vector2& vector1, const Vector2& vector2);
		// 2 つの直交ベクトル間の距離を計算します
		static constexpr float distanceSquared(const Vector2& vector1, const Vector2& vector2);
		// 2 つのベクトル間の線形補間を行います
		static constexpr Vector2 lerp(const Vector2& value1, const Vector2& value2, float amount);
		// 2 つのベクトル間の線形補間を行います
		static constexpr Vector2 lerpUnclamped(const Vector2& value1, const Vector2& value2, float amount);
		// currentからtargetへ向けて移動します
		static constexpr Vector2 moveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
		// currentからtargetへ向けて時間の経過で徐々にベクトルを変化させます
		static constexpr Vector2 smoothDamp(const Vector2& current, const Vector2& target, Vector2* currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
		// 一致する各成分ペアの最も低い値を含むベクトルを返します
		static constexpr Vector2 calculateMin(const Vector2& vector1, const Vector2& vector2);
		// 一致する各成分ペアの最も高い値を含むベクトルを返します
		static constexpr Vector2 calculateMax(const Vector2& vector1, const Vector2& vector2);
		// 値を指定された範囲内に制限します
		static constexpr Vector2 clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
		// 大きさをmaxLengthまで制限した値を取得します
		static constexpr Vector2 clampLength(const Vector2& vector1, float maxLength);
		// 引数のベクトルの垂直方向のベクトルを取得
		static constexpr Vector2 perpendicular(const Vector2& inDirection);
		// 法線を基準にしてベクトルに反射したベクトルを取得します
		static constexpr Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
		// 2つのベクトルの各成分を乗算する
		static constexpr Vector2 scale(const Vector2& vector1, const Vector2& vector2);

	public:
		
		// ベクトルの長さ
		constexpr float length() const;
		// ベクトルの長さの平方
		constexpr float lengthSquared() const;
		// 単位ベクトルを取得する
		constexpr Vector2 normalized() const;
		// 自身と引数の値が大体同じだったら真を返す
		constexpr bool equals(const Vector2& other);
		// 値を再設定する
		constexpr void setValue(float x, float y);

		// ベクトルの値を文字列に起こした物を取得
		std::string toString() const;

	public:

		// 各要素
		float x{ 0.0f };
		float y{ 0.0f };
	};

	// 定数達
	constexpr Vector2 vec2Zero	= { 0.0f };
	constexpr Vector2 vec2One	= { 1.0f };
	constexpr Vector2 vec2Up	= { 0.0f,  1.0f };
	constexpr Vector2 vec2Down	= { 0.0f, -1.0f };
	constexpr Vector2 vec2Left	= { -1.0f,  0.0f };
	constexpr Vector2 vec2Right = { 1.0f,  0.0f };
	constexpr Vector2 vec2NegativeInfinity = { -std::numeric_limits<float>::infinity() };
	constexpr Vector2 vec2PositiveInfinity = {  std::numeric_limits<float>::infinity() };

	// 演算子オーバーロード達
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

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	
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
	// 指定ベクトルから単位ベクトルを作成します
	inline constexpr Vector2 Vector2::normalize(const Vector2& value)
	{
		return Vector2(value).normalized();
	}
	// 2つのベクトルのなす角を返す
	inline constexpr float Vector2::angle(const Vector2& vector1, const Vector2& vector2)
	{
		float denominator = helper::sqrt(vector1.lengthSquared() * vector2.lengthSquared());

		if (denominator == 0.0f) return 0.0f;

		float dotValue = helper::clamp(dot(vector1, vector2) / denominator, -1.0f, 1.0f);

		return helper::acos(dotValue);
	}
	// ２つのベクトルの間の角度を取得
	inline constexpr float Vector2::signedAngle(const Vector2& vector1, const Vector2& vector2)
	{
		float unSignedAngle = angle(vector1, vector2);

		// TODO : 曖昧な変数名を直す
		float value = vector1.x * vector2.y - vector1.y * vector2.x;

		return unSignedAngle * helper::sign(value);
	}
	// 2つのベクトルの内積を計算します
	inline constexpr float Vector2::dot(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y);
	}
	// 2つのベクトルの外積を計算します
	inline constexpr float Vector2::cross(const Vector2& vector1, const Vector2& vector2)
	{
		return  (vector1.x * vector2.y) - (vector1.y * vector2.x);
	}
	// 2つのベクトル間の距離を計算します
	inline constexpr float Vector2::distance(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector2 - vector1).length();
	}
	// 2 つの直交ベクトル間の距離を計算します
	inline constexpr float Vector2::distanceSquared(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector2 - vector1).lengthSquared();
	}
	// 2 つのベクトル間の線形補間を行います
	inline constexpr Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, float amount)
	{
		return Vector2(helper::lerp(value1.x, value2.x, amount), helper::lerp(value1.y, value2.y, amount));
	}
	// 2 つのベクトル間の線形補間を行います
	inline constexpr Vector2 Vector2::lerpUnclamped(const Vector2& value1, const Vector2& value2, float amount)
	{
		return Vector2(helper::lerpUnclamped(value1.x, value2.x, amount), helper::lerpUnclamped(value1.y, value2.y, amount));
	}
	// currentからtargetへ向けて移動します
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
	// currentからtargetへ向けて時間の経過で徐々にベクトルを変化させます
	inline constexpr Vector2 Vector2::smoothDamp(const Vector2& current, const Vector2& target, Vector2* currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		smoothTime = std::max(0.0001f, smoothTime);
		float omega = 2.0f / smoothTime;

		float x = omega * deltaTime;
		// TODO : 謎の数字に謎の式
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
	// 一致する各成分ペアの最も低い値を含むベクトルを返します
	inline constexpr Vector2 Vector2::calculateMin(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(std::min(vector1.x, vector2.x), std::min(vector1.y, vector2.y));
	}
	// 一致する各成分ペアの最も高い値を含むベクトルを返します
	inline constexpr Vector2 Vector2::calculateMax(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(std::max(vector1.x, vector2.x), std::min(vector1.y, vector2.y));
	}
	// 値を指定された範囲内に制限します
	inline constexpr Vector2 Vector2::clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
	{
		return Vector2(helper::clamp(value1.x, min.x, max.x), helper::clamp(value1.y, min.y, max.y));
	}
	// 大きさをmaxLengthまで制限した値を取得します
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
	// 引数のベクトルの垂直方向のベクトルを取得
	inline constexpr Vector2 Vector2::perpendicular(const Vector2& inDirection)
	{
		return Vector2(-inDirection.y, inDirection.x);
	}
	// 法線を基準にしてベクトルに反射したベクトルを取得します
	inline constexpr Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal)
	{
		float factor = -2.0f * dot(inNormal, inDirection);

		return Vector2(factor * inNormal.x + inDirection.x, factor * inNormal.y + inDirection.y);
	}
	// 2つのベクトルの各成分を乗算する
	inline constexpr Vector2 Vector2::scale(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(vector1.x * vector2.x, vector1.y * vector2.y);
	}
	// ベクトルの長さ
	inline constexpr float Vector2::length() const
	{
		return helper::sqrt(dot(*this, *this));
	}
	// ベクトルの長さの平方
	inline constexpr float Vector2::lengthSquared() const
	{
		return dot(*this, *this);
	}
	// 単位ベクトルを取得する
	inline constexpr Vector2 Vector2::normalized() const
	{
		float len = length();

		if (len > helper::kEpsilon)
		{
			return Vector2(x / len, y / len);
		}
		return vec2Zero;
	}
	// 自身と引数の値が大体同じだったら真を返す
	inline constexpr bool Vector2::equals(const Vector2& other)
	{
		return (helper::equals(x, other.x) && helper::equals(y, other.y));
	}
	// 値を再設定する
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