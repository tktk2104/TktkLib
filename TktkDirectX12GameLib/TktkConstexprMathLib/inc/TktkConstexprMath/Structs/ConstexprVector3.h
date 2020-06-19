#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <limits>
#include <string>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include "../ConstexprMathHelper.h"

namespace tktkConstexprMath
{
	// 3次元座標・ベクトルの構造体
	struct Vector3
	{
	public:

		// コンストラクタ
		constexpr Vector3() = default;
		constexpr Vector3(float value) : x(value), y(value), z(value) {}
		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		
	public:

		// インデックスで各要素にアクセスするためのオーバーロード
		constexpr float operator[](int index) const;
		constexpr float& operator[](int index);

	public:

		// 指定ベクトルから単位ベクトルを作成します
		constexpr static Vector3 normalize(const Vector3& value);
		// ベクトルが正規化され他のベクトルと直交するようにします
		constexpr static void orthoNormalize(Vector3* normal, Vector3* tangent, Vector3* binormal);
		// ベクトルを別のベクトルに投影します
		constexpr static Vector3 project(const Vector3& value, const Vector3& onNormal);
		// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
		constexpr static Vector3 projectOnPlane(const Vector3& value, const Vector3& planeNormal);
		// 2つのベクトルの内積を計算します
		constexpr static float dot(const Vector3& vector1, const Vector3& vector2);
		// 2つのベクトルの外積を計算します
		constexpr static Vector3 cross(const Vector3& vector1, const Vector3& vector2);
		// 2つのベクトル間の距離を計算します
		constexpr static float distance(const Vector3& vector1, const Vector3& vector2);
		// 2 つの直交ベクトル間の距離を計算します 
		constexpr static float distanceSquared(const Vector3& vector1, const Vector3& vector2);
		// 2 つのベクトル間の線形補間を行います
		constexpr static Vector3 lerp(const Vector3& value1, const Vector3& value2, float amount);
		// 2 つのベクトル間の線形補間を行います
		constexpr static Vector3 lerpUnclamped(const Vector3& value1, const Vector3& value2, float amount);
		// currentからtargetへ向けて移動します
		constexpr static Vector3 moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);
		// 一致する各成分ペアの最も低い値を含むベクトルを返します
		constexpr static Vector3 calculateMin(const Vector3& vector1, const Vector3& vector2);
		// 一致する各成分ペアの最も高い値を含むベクトルを返します
		constexpr static Vector3 calculateMax(const Vector3& vector1, const Vector3& vector2);
		//	値を指定された範囲内に制限します
		constexpr static Vector3 clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
		// 大きさをmaxLengthまで制限した値を取得します
		constexpr static Vector3 clampLength(const Vector3& value, float maxLength);
		// 法線を基準にしてベクトルに反射したベクトルを取得します
		constexpr static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);
		// 2つのベクトルの各成分を乗算する
		constexpr static Vector3 scale(const Vector3& vector1, const Vector3& vector2);
		// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
		constexpr static Vector3 smoothDamp(const Vector3& cur, const Vector3& target, Vector3* curVelocity, float smoothTime, float deltaTime, float maxSpeed = INFINITY);
		// ヨー・ピッチからベクトルを作成
		constexpr static Vector3 createFromYawPitch(float yaw, float pitch);
		// ２つのベクトル間の鋭角を返します
		// TODO : コンパイル時定数関数に対応する
		static float angle(const Vector3& from, const Vector3& to);
		// fromとtoの間の度数で符号付き角度を返します
		// TODO : コンパイル時定数関数に対応する
		static float signedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);

	public:

		// ベクトルの長さを計算します
		constexpr float length() const;
		// ベクトルの長さの平方を計算します
		constexpr float lengthSquared() const;
		// 単位ベクトルを作成します
		constexpr Vector3 normalized() const;
		// 自身と引数の値が大体同じだったら真を返す
		constexpr bool equals(const Vector3& other);
		// 値を再設定する
		constexpr void setValue(float x, float y, float z);
		// ピッチを取得
		// TODO : コンパイル時定数関数に対応する
		float pitch() const;
		// ヨーを取得
		// TODO : コンパイル時定数関数に対応する
		float yaw() const;

		// ベクトルの値を文字列に起こした物を取得
		std::string toString() const;

	public:

		// 各要素
		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
	};

	// 定数達
	constexpr Vector3 vec3Zero			= {  0.0f };
	constexpr Vector3 vec3One			= {  1.0f };
	constexpr Vector3 vec3Up			= {  0.0f,  1.0f,  0.0f };
	constexpr Vector3 vec3Down			= {  0.0f, -1.0f,  0.0f };
	constexpr Vector3 vec3Left			= { -1.0f,  0.0f,  0.0f };
	constexpr Vector3 vec3Right			= {  1.0f,  0.0f,  0.0f };
	constexpr Vector3 vec3ForwardLH		= {  0.0f,  0.0f,  1.0f };	//（DirectX等）
	constexpr Vector3 vec3BackwardLH	= {  0.0f,  0.0f, -1.0f };	//（DirectX等）
	constexpr Vector3 vec3ForwardRH		= {  0.0f,  0.0f, -1.0f };	//（OpenGL等）
	constexpr Vector3 vec3BackwardRH	= {  0.0f,  0.0f,  1.0f };	//（OpenGL等）
	constexpr Vector3 vec3NegativeInfinity = { -std::numeric_limits<float>::infinity() };
	constexpr Vector3 vec3PositiveInfinity = {  std::numeric_limits<float>::infinity() };

	// 演算子オーバーロード達
	constexpr Vector3	operator -  (const Vector3& v);
	constexpr Vector3&	operator += (Vector3& v1, const Vector3& v2);
	constexpr Vector3&	operator -= (Vector3& v1, const Vector3& v2);
	constexpr Vector3&	operator *= (Vector3& v, float s);
	constexpr Vector3&	operator /= (Vector3& v, float s);
	constexpr Vector3	operator +  (Vector3 v1, const Vector3& v2);
	constexpr Vector3	operator -  (Vector3 v1, const Vector3& v2);
	constexpr Vector3	operator *  (Vector3 v, float s);
	constexpr Vector3	operator *  (float s, Vector3 v);
	constexpr Vector3	operator /  (Vector3 v, float s);
	constexpr bool		operator == (const Vector3& lhs, const Vector3& rhs);
	constexpr bool		operator != (const Vector3& lhs, const Vector3& rhs);
	std::ostream&		operator << (std::ostream& os, const Vector3& vector3);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	inline constexpr float Vector3::operator[](int index) const
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		}
		throw std::runtime_error("vector3 operator[] out of range");
	}

	inline constexpr float& Vector3::operator[](int index)
	{
		switch (index)
		{
		case 0: return x; break;
		case 1: return y; break;
		case 2: return z; break;
		}
		throw std::runtime_error("vector3 operator[] out of range");
	}
	// 指定ベクトルから単位ベクトルを作成します
	inline constexpr Vector3 Vector3::normalize(const Vector3& value)
	{
		return Vector3(value).normalized();
	}
	// ベクトルが正規化され他のベクトルと直交するようにします
	inline constexpr void Vector3::orthoNormalize(Vector3* normal, Vector3* tangent, Vector3* binormal)
	{
		*normal = Vector3::normalize(*normal);

		if (normal->lengthSquared() <= (helper::kEpsilon * helper::kEpsilon))
		{
			*normal = vec3Right;
		}

		Vector3 bn = Vector3::cross(*normal, *tangent);

		if (bn.lengthSquared() <= (helper::kEpsilon * helper::kEpsilon))
		{
			*tangent = Vector3::cross(vec3ForwardLH, *normal);
		}

		if (tangent->lengthSquared() <= (helper::kEpsilon * helper::kEpsilon))
		{
			*tangent = Vector3::cross(vec3Right, *normal);
		}

		bn = Vector3::cross(*normal, *tangent);
		bn = Vector3::normalize(bn);

		*tangent = Vector3::cross(bn, *normal);
		*binormal = (Vector3::dot(bn, *binormal) < 0.0f) ? -bn : bn;
	}
	// ベクトルを別のベクトルに投影します
	inline constexpr Vector3 Vector3::project(const Vector3& value, const Vector3& onNormal)
	{
		float sqrLen = onNormal.lengthSquared();

		if (sqrLen < helper::kEpsilon) return vec3Zero;

		float dotValue = dot(value, onNormal);

		return Vector3(
			onNormal.x * dotValue / sqrLen,
			onNormal.y * dotValue / sqrLen,
			onNormal.z * dotValue / sqrLen
		);
	}
	// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
	inline constexpr Vector3 Vector3::projectOnPlane(const Vector3& value, const Vector3& planeNormal)
	{
		float sqrLen = planeNormal.lengthSquared();
		
		if (sqrLen < helper::kEpsilon) return value;
		
		float dotValue = dot(value, planeNormal);
		
		return Vector3(
			value.x - planeNormal.x * dotValue / sqrLen,
			value.y - planeNormal.y * dotValue / sqrLen,
			value.z - planeNormal.z * dotValue / sqrLen
		);
	}
	// 2つのベクトルの内積を計算します
	inline constexpr float Vector3::dot(const Vector3& vector1, const Vector3& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
	}
	// 2つのベクトルの外積を計算します
	inline constexpr Vector3 Vector3::cross(const Vector3& vector1, const Vector3& vector2)
	{
		return Vector3(
			vector1.y * vector2.z - vector1.z * vector2.y,
			vector1.z * vector2.x - vector1.x * vector2.z,
			vector1.x * vector2.y - vector1.y * vector2.x
		);
	}
	// 2つのベクトル間の距離を計算します
	inline constexpr float Vector3::distance(const Vector3& vector1, const Vector3& vector2)
	{
		return (vector2 - vector1).length();
	}
	// 2 つの直交ベクトル間の距離を計算します 
	inline constexpr float Vector3::distanceSquared(const Vector3& vector1, const Vector3& vector2)
	{
		return 	(vector2 - vector1).lengthSquared();
	}
	// 2 つのベクトル間の線形補間を行います
	inline constexpr Vector3 Vector3::lerp(const Vector3& value1, const Vector3& value2, float amount)
	{
		return Vector3(
			helper::lerp(value1.x, value2.x, amount),
			helper::lerp(value1.y, value2.y, amount),
			helper::lerp(value1.z, value2.z, amount)
		);
	}
	// 2 つのベクトル間の線形補間を行います
	inline constexpr Vector3 Vector3::lerpUnclamped(const Vector3& value1, const Vector3& value2, float amount)
	{
		return Vector3(
			helper::lerpUnclamped(value1.x, value2.x, amount),
			helper::lerpUnclamped(value1.y, value2.y, amount),
			helper::lerpUnclamped(value1.z, value2.z, amount)
		);
	}
	// currentからtargetへ向けて移動します
	inline constexpr Vector3 Vector3::moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta)
	{
		float toVector_x = target.x - current.x;
		float toVector_y = target.y - current.y;
		float toVector_z = target.z - current.z;
		
		float sqdist = (toVector_x * toVector_x) + (toVector_y * toVector_y) + (toVector_z * toVector_z);
		
		if (sqdist == 0 || sqdist <= (maxDistanceDelta * maxDistanceDelta))
		{
			return target;
		}
		
		float dist = helper::sqrt(sqdist);
		
		return Vector3(
			current.x + toVector_x / dist * maxDistanceDelta,
			current.y + toVector_y / dist * maxDistanceDelta,
			current.z + toVector_z / dist * maxDistanceDelta
		);
	}
	// 一致する各成分ペアの最も低い値を含むベクトルを返します
	inline constexpr Vector3 Vector3::calculateMin(const Vector3& vector1, const Vector3& vector2)
	{
		return Vector3(
			std::min(vector1.x, vector2.x),
			std::min(vector1.y, vector2.y),
			std::min(vector1.z, vector2.z)
		);
	}
	// 一致する各成分ペアの最も高い値を含むベクトルを返します
	inline constexpr Vector3 Vector3::calculateMax(const Vector3& vector1, const Vector3& vector2)
	{
		return Vector3(
			std::max(vector1.x, vector2.x),
			std::max(vector1.y, vector2.y),
			std::max(vector1.z, vector2.z)
		);
	}
	//	値を指定された範囲内に制限します
	inline constexpr Vector3 Vector3::clamp(const Vector3& value1, const Vector3& min, const Vector3& max)
	{
		return Vector3(
			helper::clamp(value1.x, min.x, max.x),
			helper::clamp(value1.y, min.y, max.y),
			helper::clamp(value1.z, min.z, max.z)
		);
	}
	// 大きさをmaxLengthまで制限した値を取得します
	inline constexpr Vector3 Vector3::clampLength(const Vector3& value, float maxLength)
	{
		float sqrLen = value.lengthSquared();
		
		if (sqrLen < maxLength * maxLength)
		{
			float mag = std::sqrt(sqrLen);
		
			float normalized_x = value.x / mag;
			float normalized_y = value.y / mag;
			float normalized_z = value.z / mag;
		
			return Vector3(
				normalized_x * maxLength,
				normalized_y * maxLength,
				normalized_z * maxLength
			);
		}
		return value;
	}
	// 法線を基準にしてベクトルに反射したベクトルを取得します
	inline constexpr Vector3 Vector3::reflect(const Vector3& inDirection, const Vector3& inNormal)
	{
		float factor = -2.0f * dot(inNormal, inDirection);
		
		return Vector3(
			factor * inNormal.x + inDirection.x,
			factor * inNormal.y + inDirection.y,
			factor * inNormal.z + inDirection.z
		);
	}
	// 2つのベクトルの各成分を乗算する
	inline constexpr Vector3 Vector3::scale(const Vector3& vector1, const Vector3& vector2)
	{
		return Vector3(
			vector1.x * vector2.x,
			vector1.y * vector2.y,
			vector1.z * vector2.z
		);
	}
	// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
	inline constexpr Vector3 Vector3::smoothDamp(const Vector3& cur, const Vector3& target, Vector3* curVelocity, float smoothTime, float deltaTime, float maxSpeed)
	{
		float output_x = 0.0f;
		float output_y = 0.0f;
		float output_z = 0.0f;
		
		smoothTime = std::max(0.0001f, smoothTime);
		float omega = 2.0f / smoothTime;
		
		float x = omega * deltaTime;
		float exp = 1.0f / (1.0f + x + 0.48f * x + 0.235f * x * x * x);
		
		float change_x = cur.x - target.x;
		float change_y = cur.y - target.y;
		float change_z = cur.z - target.z;
		
		float maxChange = maxSpeed * smoothTime;
		
		float maxChangeSq = maxChange * maxChange;
		float sqrlen = (change_x * change_x) + (change_y * change_y) + (change_z * change_z);
		
		if (sqrlen > maxChangeSq)
		{
			float len = helper::sqrt(sqrlen);
			change_x = change_x / len * maxChange;
			change_y = change_y / len * maxChange;
			change_z = change_z / len * maxChange;
		}
		
		Vector3 result = target;
		
		result.x = cur.x - change_x;
		result.y = cur.y - change_y;
		result.z = cur.z - change_z;
		
		float temp_x = ((*curVelocity).x + omega * change_x) * deltaTime;
		float temp_y = ((*curVelocity).y + omega * change_y) * deltaTime;
		float temp_z = ((*curVelocity).z + omega * change_z) * deltaTime;
		
		(*curVelocity).x = ((*curVelocity).x - omega * temp_x) * exp;
		(*curVelocity).y = ((*curVelocity).y - omega * temp_y) * exp;
		(*curVelocity).z = ((*curVelocity).z - omega * temp_z) * exp;
		
		output_x = result.x + (change_x + temp_x) * exp;
		output_y = result.y + (change_y + temp_y) * exp;
		output_z = result.z + (change_z + temp_z) * exp;
		
		float origMinusCurrent_x = target.x - cur.x;
		float origMinusCurrent_y = target.y - cur.y;
		float origMinusCurrent_z = target.z - cur.z;
		
		float outMinusOrig_x = output_x - target.x;
		float outMinusOrig_y = output_y - target.y;
		float outMinusOrig_z = output_z - target.z;
		
		if ((origMinusCurrent_x * outMinusOrig_x)
			+ (origMinusCurrent_y * outMinusOrig_y)
			+ (origMinusCurrent_z * outMinusOrig_z) > 0)
		{
			output_x = target.x;
			output_y = target.y;
			output_z = target.z;
		
			(*curVelocity).x = (output_x - target.x) / deltaTime;
			(*curVelocity).y = (output_y - target.y) / deltaTime;
			(*curVelocity).z = (output_z - target.z) / deltaTime;
		}
		return Vector3(output_x, output_y, output_z);
	}
	// ヨー・ピッチからベクトルを作成
	inline constexpr Vector3 Vector3::createFromYawPitch(float yaw, float pitch)
	{
		return Vector3(
			 helper::cos(pitch) * helper::sin(yaw),
			-helper::sin(pitch),
			 helper::cos(pitch) * helper::cos(yaw));
	}
	// ２つのベクトル間の鋭角を返します
	inline float Vector3::angle(const Vector3& from, const Vector3& to)
	{
		float dotValue = dot(normalize(from), normalize(to));
		// 計算誤差で内積の結果が-1.0～1.0を超えるとacosはnanを返す
		return helper::acos(helper::clamp(dotValue, -1.0f, 1.0f));
	}
	// fromとtoの間の度数で符号付き角度を返します
	inline float Vector3::signedAngle(const Vector3& from, const Vector3& to, const Vector3& axis)
	{
		float unsignedAngle = angle(from, to);

		float cross_x = from.y * to.z - from.z * to.y;
		float cross_y = from.z * to.x - from.x * to.z;
		float cross_z = from.x * to.y - from.y * to.x;

		float sign = helper::sign(axis.x * cross_x + axis.y * cross_y + axis.z * cross_z);

		return unsignedAngle * sign;
	}
	// ベクトルの長さを計算します
	inline constexpr float Vector3::length() const
	{
		return helper::sqrt(lengthSquared());
	}
	// ベクトルの長さの平方を計算します
	inline constexpr float Vector3::lengthSquared() const
	{
		return dot(*this, *this);
	}
	// 単位ベクトルを作成します
	inline constexpr Vector3 Vector3::normalized() const
	{
		const float len = length();
		if (len < helper::kEpsilon) return vec3Zero;
		return Vector3(x / len, y / len, z / len);
	}
	// 自身と引数の値が大体同じだったら真を返す
	inline constexpr bool Vector3::equals(const Vector3& other)
	{
		return(
			helper::equals(x, other.x) &&
			helper::equals(y, other.y) &&
			helper::equals(z, other.z)
			);
	}
	// 値を再設定する
	inline constexpr void Vector3::setValue(float x, float y, float z)
	{
		Vector3::x = x;
		Vector3::y = y;
		Vector3::z = z;
	}
	// ピッチを取得
	inline float Vector3::pitch() const
	{
		float len = length();
		if (helper::equals(len, 0.0f)) return 0.0f;
		return helper::asin(-y / len);
	}
	// ヨーを取得
	inline float Vector3::yaw() const
	{
		if (helper::equals(length(), 0.0f)) return 0.0f;
		return helper::atan(x, z);
	}
	constexpr Vector3 operator - (const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}
	constexpr Vector3& operator += (Vector3& v1, const Vector3& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		return v1;
	}
	constexpr Vector3& operator -= (Vector3& v1, const Vector3& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		return v1;
	}
	constexpr Vector3& operator *= (Vector3& v, float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		return v;
	}
	constexpr Vector3& operator /= (Vector3& v, float s)
	{
		v.x /= s;
		v.y /= s;
		v.z /= s;
		return v;
	}
	constexpr Vector3 operator + (Vector3 v1, const Vector3& v2)
	{
		return v1 += v2;
	}
	constexpr Vector3 operator - (Vector3 v1, const Vector3& v2)
	{
		return v1 -= v2;
	}
	constexpr Vector3 operator * (Vector3 v, float s)
	{
		return v *= s;
	}
	constexpr Vector3 operator * (float s, Vector3 v)
	{
		return v *= s;
	}
	constexpr Vector3 operator / (Vector3 v, float s)
	{
		return v /= s;
	}
	constexpr bool operator==(const Vector3 & lhs, const Vector3 & rhs)
	{
		return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
	}
	constexpr bool operator!=(const Vector3 & lhs, const Vector3 & rhs)
	{
		return !(lhs == rhs);
	}
}
#endif