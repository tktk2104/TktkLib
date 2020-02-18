#ifndef MMD_MATH_H_
#define MMD_MATH_H_

#include "MMDTypes.h"
#include <cmath>

namespace mmd {

inline float to_radian(float degree) {
	return degree * (3.1415926535f / 180.0f);
}

inline float to_degree(float radian) {
	return radian * (180.0f / 3.1415926535f);
}

struct matrix {
	float m[4][4];

	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	matrix(
		float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f,
		float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
		float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
		float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f
		)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}
	// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
	matrix(const float4& q) {
		float xx = q.x * q.x * 2.0f;
		float yy = q.y * q.y * 2.0f;
		float zz = q.z * q.z * 2.0f;
		float xy = q.x * q.y * 2.0f;
		float xz = q.x * q.z * 2.0f;
		float yz = q.y * q.z * 2.0f;
		float wx = q.w * q.x * 2.0f;
		float wy = q.w * q.y * 2.0f;
		float wz = q.w * q.z * 2.0f;

		m[0][0] = 1.0f - (yy + zz);
		m[0][1] = xy + wz;
		m[0][2] = xz - wy;
		m[0][3] = 0.0f;

		m[1][0] = xy - wz;
		m[1][1] = 1.0f - (xx + zz);
		m[1][2] = yz + wx;
		m[1][3] = 0.0f;

		m[2][0] = xz + wy;
		m[2][1] = yz - wx;
		m[2][2] = 1.0f - (xx + yy);
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}
	// ’PˆÊs—ñ‰»
	matrix& identity() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		return *this;
	}
	// Šg‘åk¬‚ğ‡¬
	matrix& scale(const float3& s) {
		return *this *= matrix(
			s.x, 0.0f, 0.0f, 0.0f,
			0.0f, s.y, 0.0f, 0.0f,
			0.0f, 0.0f, s.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}
	// X²‰ñ‚è‚Ì‰ñ“]‚ğ‡¬
	matrix& rotateX(float degree) {
		matrix rx;
		rx.m[1][1] = std::cos(to_radian(degree));
		rx.m[1][2] = std::sin(to_radian(degree));
		rx.m[2][1] = -rx.m[1][2];
		rx.m[2][2] =  rx.m[1][1];
		return *this *= rx;
	}
	// Y²‰ñ‚è‚Ì‰ñ“]‚ğ‡¬
	matrix& rotateY(float degree) {
		matrix ry;
		ry.m[0][0] = std::cos(to_radian(degree));
		ry.m[2][0] = std::sin(to_radian(degree));
		ry.m[0][2] = -ry.m[2][0];
		ry.m[2][2] =  ry.m[0][0];
		return *this *= ry;
	}
	// Z²‰ñ‚è‚Ì‰ñ“]‚ğ‡¬
	matrix& rotateZ(float degree) {
		matrix rz;
		rz.m[0][0] = std::cos(to_radian(degree));
		rz.m[0][1] = std::sin(to_radian(degree));
		rz.m[1][0] = -rz.m[0][1];
		rz.m[1][1] =  rz.m[0][0];
		return *this *= rz;
	}
	// •½sˆÚ“®‚ğ‡¬
	matrix& translate(const float3& t) {
		return *this *= matrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			t.x, t.y, t.z, 1.0f
			);
	}
	// ‰ñ“]‚ğæ“¾
	float4 getRotate() const {
		float4 result;
		float tr = m[0][0] + m[1][1] + m[2][2] + m[3][3];
		if (tr >= 1.0f) {
			const float fourD = 2.0f * std::sqrt(tr);
			result.x = (m[1][2] - m[2][1]) / fourD;
			result.y = (m[2][0] - m[0][2]) / fourD;
			result.z = (m[0][1] - m[1][0]) / fourD;
			result.w = fourD / 4.0f;
			return result;
		}
		int i = 0;
		if (m[0][0] <= m[1][1]) {
			i = 1;
		}
		if (m[2][2] > m[i][i]) {
			i = 2;
		}
		const int j = (i + 1) % 3;
		const int k = (j + 1) % 3;
		tr = m[i][i] - m[j][j] - m[k][k] + 1.0f;
		const float fourD = 2.0f * std::sqrt(tr);
		float qa[4];
		qa[i] = fourD / 4.0f;
		qa[j] = (m[j][i] + m[i][j]) / fourD;
		qa[k] = (m[k][i] + m[i][k]) / fourD;
		qa[3] = (m[j][k] - m[k][j]) / fourD;
		result.x = qa[0];
		result.y = qa[1];
		result.z = qa[2];
		result.w = qa[3];
		return result;
	}
	// À•W‚ğæ“¾
	float3 getTranslate() const {
		float3 result;
		result.x = m[3][0]; result.y = m[3][1]; result.z = m[3][2];
		return result;
	}
	// À•W‚Ì•ÏŠ·
	float3 transformPoint(const float3& v) const {
		float3 result;
		const float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
		result.x = (v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0]) / w;
		result.y = (v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1]) / w;
		result.z = (v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]) / w;
		return result;
	}
	// ƒNƒH[ƒ^ƒjƒIƒ“‚Ì•ÏŠ·
	float4 transformQuaternion(const float4& q) const {
		return (matrix(q) * (*this)).getRotate();
	}
	// –@üƒxƒNƒgƒ‹‚Ì•ÏŠ·
	float3 transformNormal(const float3& v) const {
		float3 result;
		result.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
		result.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
		result.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
		return result;
	}
	// ‹ts—ñ
	matrix inverse() const
	{
		const float a0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		const float a1 = m[0][0] * m[1][2] - m[0][2] * m[1][0];
		const float a2 = m[0][0] * m[1][3] - m[0][3] * m[1][0];
		const float a3 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
		const float a4 = m[0][1] * m[1][3] - m[0][3] * m[1][1];
		const float a5 = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		const float b0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
		const float b1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
		const float b2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
		const float b3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
		const float b4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
		const float b5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		const float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
		if (det == 0.0f) {
			return *this; // ‹ts—ñ‚ª‘¶İ‚µ‚È‚¢I
		}
		const float invDet = 1.0f / det;
		return matrix(
			(m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3) * invDet,
			(-m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3) * invDet,
			(m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3) * invDet,
			(-m[2][1] * a5 + m[2][2] * a4 - m[2][3] * a3) * invDet,
			(-m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1) * invDet,
			(m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1) * invDet,
			(-m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1) * invDet,
			(m[2][0] * a5 - m[2][2] * a2 + m[2][3] * a1) * invDet,
			(m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0) * invDet,
			(-m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0) * invDet,
			(m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0) * invDet,
			(-m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0) * invDet,
			(-m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0) * invDet,
			(m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0) * invDet,
			(-m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0) * invDet,
			(m[2][0] * a3 - m[2][1] * a1 + m[2][2] * a0) * invDet
		);
	}
	// Š|‚¯Z
	matrix& operator *= (const matrix& r) {
		matrix result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] = 0.0f;
				for (int k = 0; k < 4; ++k) {
					result.m[i][j] += m[i][k] * r.m[k][j];
				}
			}
		}
		*this = result;
		return *this;
	}
	// Š|‚¯Z
	matrix operator * (const matrix& r) const {
		matrix result(*this);
		return result *= r;
	}
	// Š|‚¯Z
	matrix& operator *= (float s) {
		matrix result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] *= s;
			}
		}
		return *this;
	}
	// Š|‚¯Z
	matrix operator * (float s) const {
		matrix result(*this);
		return result *= s;
	}
	// ‘«‚µZ
	matrix& operator += (const matrix& r) {
		matrix result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] += r.m[i][j];
			}
		}
		return *this;
	}
	// ‘«‚µZ
	matrix operator + (const matrix& r) const {
		matrix result(*this);
		return result += r;
	}
};

inline bool operator < (const float2& l, const float2& r) {
	if (l.x != r.x) return l.x < r.x;
	if (l.y != r.y) return l.y < r.y;
	return false;
}

inline bool operator == (const float2& l, const float2& r) {
	return (l.x == r.x) && (l.y == r.y);
}

inline bool operator != (const float2& l, const float2& r) {
	return !(l == r);
}

inline bool operator < (const float3& l, const float3& r) {
	if (l.x != r.x) return l.x < r.x;
	if (l.y != r.y) return l.y < r.y;
	if (l.z != r.z) return l.z < r.z;
	return false;
}

inline bool operator == (const float3& l, const float3& r) {
	return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}

inline bool operator != (const float3& l, const float3& r) {
	return !(l == r);
}

inline float3 operator - (float3& v) {
	float3 result;
	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return result;
}

inline float3& operator += (float3& l, const float3& r) {
	l.x += r.x;
	l.y += r.y;
	l.z += r.z;
	return l;
}

inline float3& operator -= (float3& l, const float3& r) {
	l.x -= r.x;
	l.y -= r.y;
	l.z -= r.z;
	return l;
}

inline float3& operator *= (float3& l, float s) {
	l.x *= s;
	l.y *= s;
	l.z *= s;
	return l;
}

inline float3& operator /= (float3& l, float s) {
	l.x /= s;
	l.y /= s;
	l.z /= s;
	return l;
}

inline float3 operator + (float3 l, const float3& r) {
	return l += r;
}

inline float3 operator - (float3 l, const float3& r) {
	return l -= r;
}

inline float3 operator * (float3 l, float s) {
	return l *= s;
}

inline float3 operator * (float s, float3 l) {
	return l *= s;
}

inline float3 operator / (float3 l, float s) {
	return l /= s;
}

inline float dot(const float3& l, const float3& r) {
	return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
}

inline float3 cross(const float3& l, const float3& r) {
	float3 result;
	result.x = l.y * r.z - l.z * r.y;
	result.y = l.z * r.x - l.x * r.z;
	result.z = l.x * r.y - l.y * r.x;
	return result;
}

inline float length(const float3& v) {
	return std::sqrt(dot(v, v));
}

inline float3 normalize(const float3& v) {
	float len = length(v);
	if (len < FLT_EPSILON) return v;
	return v / len;
}

inline float3 lerp(const float3& l, const float3& r, float t) {
	return (l * (1.0f - t)) + (r * t);
}

inline bool operator < (const float4& l, const float4& r) {
	if (l.x != r.x) return l.x < r.x;
	if (l.y != r.y) return l.y < r.y;
	if (l.z != r.z) return l.z < r.z;
	if (l.w != r.w) return l.w < r.w;
	return false;
}

inline bool operator == (const float4& l, const float4& r) {
	return (l.x == r.x) && (l.y == r.y) && (l.z == r.z) && (l.w == r.w);
}

inline bool operator != (const float4& l, const float4& r) {
	return !(l == r);
}

float dot(const float4& l, const float4& r) {
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}

float length(const float4& q) {
	return std::sqrt(dot(q, q));
}

inline float4 normalize(const float4& q) {
	float4 result(q);
	const float len = length(q);
	if (len != 0.0f) {
		result.x /= len;
		result.y /= len;
		result.z /= len;
		result.w /= len;
	}
	return result;
}

inline float4 slerp(const float4& l, const float4& r, float t)
{
	float4 temp(r);
	float cos = dot(l, r);
	if (cos < 0.0f) {
		cos = -cos;
		temp.x = -temp.x;
		temp.y = -temp.y;
		temp.z = -temp.z;
		temp.w = -temp.w;
	}
	float k0 = 1.0f - t;
	float k1 = t;
	if ((1.0f - cos) > 0.001f) {
		const float theta = std::acos(cos);
		k0 = std::sin(theta*k0) / std::sin(theta);
		k1 = std::sin(theta*k1) / std::sin(theta);
	}
	float4 result;
	result.x = l.x * k0 + temp.x * k1;
	result.y = l.y * k0 + temp.y * k1;
	result.z = l.z * k0 + temp.z * k1;
	result.w = l.w * k0 + temp.w * k1;
	return normalize(result);
}

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
float4 axis_degree_to_quaternion(const float4& axis_degree)
{
	float4 result;
	const float sin = std::sin(to_radian(axis_degree.w / 2.0f));
	result.x = sin * axis_degree.x;
	result.y = sin * axis_degree.y;
	result.z = sin * axis_degree.z;
	result.w = std::cos(to_radian(axis_degree.w / 2.0f));
	return result;
}

}

#endif

// end of file
