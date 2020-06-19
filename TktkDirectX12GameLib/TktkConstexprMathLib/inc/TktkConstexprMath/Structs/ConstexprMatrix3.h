#ifndef MATRIX3_H_
#define MATRIX3_H_

#include <string>
#include <ostream>
#include "ConstexprVector2.h"
#include "../ConstexprMathHelper.h"

namespace tktkConstexprMath
{
	// 3x3の行列の構造体
	struct Matrix3
	{
	public:

		// コンストラクタ
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

		// 移動行列を生成
		static constexpr Matrix3 createTranslation(const Vector2& translation);
		// 回転行列を生成
		static constexpr Matrix3 createRotation(float degree);
		// スケール行列を生成
		static constexpr Matrix3 createScale(const Vector2& scale);
		// 移動、回転、スケールの値から行列を生成
		static constexpr Matrix3 createTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// 逆行列を生成
		static constexpr Matrix3 calculateInvert(const Matrix3& matrix);
		// 行列の行と列を入れ替えます
		static constexpr Matrix3 calculateTranspose(const Matrix3& matrix);
		// 第一引数のVec2を第二引数の行列を使って座標変換する
		static constexpr Vector2 transformVec(const Vector2& position, const Matrix3& matrix);

		//// 逆行列を生成（回転と平行移動のみ）
		//static Matrix3 calculateInvertFast(const Matrix3& matrix);
		// 2つの行列の対応する値の間を線形補間します
		//static Matrix3 lerp(const Matrix3& value1, const Matrix3& value2, float amount);

	public:

		// 平行移動ベクトルを設定
		constexpr void setTranslation(const Vector2& translation);
		// 移動、回転、スケールの値を再設定
		constexpr void setTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// 平行移動ベクトルを計算
		constexpr Vector2 calculateTranslation() const;
		// 回転を計算
		// TODO : コンパイル時定数関数に対応する
		float calculateRotation() const;
		// スケール値を計算
		constexpr Vector2 calculateScale() const;
		// 上方ベクトルを計算
		constexpr Vector2 calculateUp() const;
		// 右ベクトルを計算
		constexpr Vector2 calculateRight() const;

		// フォーマットされた文字列に変換
		std::string toString() const;

	public:

		// 各要素
		float m[3][3]{
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f }
		};
	};

	// 定数達
	constexpr Matrix3 mat3Zero		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix3 mat3Identity	{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// 演算子オーバーロード達
	constexpr Matrix3	operator -  (const Matrix3& m);
	constexpr Matrix3&	operator += (Matrix3& m1, const Matrix3& m2);
	constexpr Matrix3&	operator -= (Matrix3& m1, const Matrix3& m2);
	constexpr Matrix3&	operator *= (Matrix3& m1, const Matrix3& m2);
	constexpr Matrix3&	operator *= (Matrix3& m, float s);
	constexpr Matrix3&	operator /= (Matrix3& m, float s);
	constexpr Matrix3	operator +  (Matrix3 m1, const Matrix3& m2);
	constexpr Matrix3	operator -  (Matrix3 m1, const Matrix3& m2);
	constexpr Matrix3	operator *  (Matrix3 m1, const Matrix3& m2);
	constexpr Matrix3	operator *  (Matrix3 m, float s);
	constexpr Matrix3	operator *  (float s, Matrix3 m);
	constexpr Matrix3	operator /  (Matrix3 m, float s);
	constexpr Vector2	operator *	(const Vector2& v, const Matrix3& m);
	constexpr Vector2&	operator *=	(Vector2& v, const Matrix3& m);
	std::ostream&		operator << (std::ostream& os, const Matrix3& matrix);

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 移動行列を生成
	inline constexpr Matrix3 Matrix3::createTranslation(const Vector2& translation)
	{
		return Matrix3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			translation.x, translation.y, 1.0f
		);
	}
	// 回転行列を生成
	inline constexpr Matrix3 Matrix3::createRotation(float degree)
	{
		float sinValue = helper::sin(degree);
		float cosValue = helper::cos(degree);

		return Matrix3(
			 cosValue,	sinValue,	0.0f,
			-sinValue,	cosValue,	0.0f,
			 0.0f,		0.0f,		1.0f
		);
	}
	// スケール行列を生成
	inline constexpr Matrix3 Matrix3::createScale(const Vector2& scale)
	{
		return Matrix3(
			scale.x,	0.0f,		0.0f,
			0.0f,		scale.y,	0.0f,
			0.0f,		0.0f,		1.0f
		);
	}
	// 移動、回転、スケールの値から行列を生成
	inline constexpr Matrix3 Matrix3::createTRS(const Vector2& translation, float rotate, const Vector2& scale)
	{
		Matrix3 result = createRotation(rotate);

		result.m[0][0] *= scale.x;			result.m[0][1] *= scale.x;
		result.m[1][0] *= scale.y;			result.m[1][1] *= scale.y;
		result.m[2][0] = translation.x;		result.m[2][1] = translation.y;

		return result;
	}
	// 逆行列を生成
	inline constexpr Matrix3 Matrix3::calculateInvert(const Matrix3& matrix)
	{
		float a1 = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2];
		float a2 = matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0];
		float a3 = matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1];
		float a4 = matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0];
		float a5 = matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2];
		float a6 = matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

		float det = a1 + a2 + a3 - a4 - a5 - a6;

		if (det < helper::kEpsilon)
		{
			return matrix; // 逆行列が存在しない
		}
		float invDet = 1.0f / det;

		return Matrix3(
			 (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * invDet,
			-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * invDet,
			 (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * invDet,

			-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * invDet,
			 (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * invDet,
			-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * invDet,

			 (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * invDet,
			-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * invDet,
			 (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * invDet
		);
	}
	// 行列の行と列を入れ替えます
	inline constexpr Matrix3 Matrix3::calculateTranspose(const Matrix3& matrix)
	{
		return Matrix3(
			matrix.m[0][0], matrix.m[1][0], matrix.m[2][0],
			matrix.m[0][1], matrix.m[1][1], matrix.m[2][1],
			matrix.m[0][2], matrix.m[1][2], matrix.m[2][2]
		);
	}

	// 第一引数のVec2を第二引数の行列を使って座標変換する
	inline constexpr Vector2 Matrix3::transformVec(const Vector2& position, const Matrix3& matrix)
	{
		float w = position.x * matrix.m[0][2] + position.y * matrix.m[1][2] + matrix.m[2][2];

		return Vector2(
			(position.x * matrix.m[0][0] + position.y * matrix.m[1][0] + matrix.m[2][0]) / w,
			(position.x * matrix.m[0][1] + position.y * matrix.m[1][1] + matrix.m[2][1]) / w
		);
	}
	// 平行移動ベクトルを設定
	inline constexpr void Matrix3::setTranslation(const Vector2& translation)
	{
		m[2][0] = translation.x; m[2][1] = translation.y;
	}
	// 移動、回転、スケールの値を再設定
	inline constexpr void Matrix3::setTRS(const Vector2& translation, float rotate, const Vector2& scale)
	{
		Matrix3 result = createTRS(translation, rotate, scale);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] = result.m[i][j];
			}
		}
	}
	// 平行移動ベクトルを計算
	inline constexpr Vector2 Matrix3::calculateTranslation() const
	{
		return Vector2(m[2][0], m[2][1]);
	}
	// 回転を計算
	inline float Matrix3::calculateRotation() const
	{
		return helper::acos(m[0][0] / calculateRight().length()) * helper::sign(m[0][1]);
	}
	// スケール値を計算
	inline constexpr Vector2 Matrix3::calculateScale() const
	{
		return Vector2(calculateRight().length(), calculateUp().length());
	}
	// 上方ベクトルを計算
	inline constexpr Vector2 Matrix3::calculateUp() const
	{
		return Vector2(-m[1][0], -m[1][1]);
	}
	// 右ベクトルを計算
	inline constexpr Vector2 Matrix3::calculateRight() const
	{
		return Vector2(m[0][0], m[0][1]);
	}
	constexpr Matrix3 operator-(const Matrix3& m)
	{
		return Matrix3(
			-m.m[0][0], -m.m[0][1], -m.m[0][2],
			-m.m[1][0], -m.m[1][1], -m.m[1][2],
			-m.m[2][0], -m.m[2][1], -m.m[2][2]);
	}
	constexpr Matrix3& operator+=(Matrix3& m1, const Matrix3& m2)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m1.m[i][j] += m2.m[i][j];
			}
		}
		return m1;
	}
	constexpr Matrix3& operator-=(Matrix3& m1, const Matrix3& m2)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m1.m[i][j] -= m2.m[i][j];
			}
		}
		return m1;
	}
	constexpr Matrix3& operator*=(Matrix3& m1, const Matrix3& m2)
	{
		Matrix3 result = mat3Zero;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					result.m[i][j] += m1.m[i][k] * m2.m[k][j];
				}
			}
		}
		m1 = result;
		return m1;
	}
	constexpr Matrix3& operator*=(Matrix3& m, float s)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m.m[i][j] *= s;
			}
		}
		return m;
	}
	constexpr Matrix3& operator/=(Matrix3& m, float s)
	{
		return m *= (1.0f / s);
	}
	constexpr Matrix3 operator+(Matrix3 m1, const Matrix3& m2)
	{
		return m1 += m2;
	}
	constexpr Matrix3 operator-(Matrix3 m1, const Matrix3& m2)
	{
		return m1 -= m2;
	}
	constexpr Matrix3 operator*(Matrix3 m1, const Matrix3& m2)
	{
		return m1 *= m2;
	}
	constexpr Matrix3 operator*(Matrix3 m, float s)
	{
		return m *= s;
	}
	constexpr Matrix3 operator*(float s, Matrix3 m)
	{
		return m *= s;
	}
	constexpr Matrix3 operator/(Matrix3 m, float s)
	{
		return m /= s;
	}
	constexpr Vector2 operator*(const Vector2& v, const Matrix3& m)
	{
		return Matrix3::transformVec(v, m);
	}
	constexpr Vector2& operator*=(Vector2& v, const Matrix3& m)
	{
		v = v * m; return v;
	}
}
#endif