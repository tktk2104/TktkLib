#ifndef COLOR_H_
#define COLOR_H_

#include <ostream>
#include <string>
#include <algorithm>
#include "../MathHelper.h"

namespace tktkMath
{
	// �F���̍\����
	struct Color
	{
	public:

		// �R���X�g���N�^
		constexpr Color() = default;
		constexpr Color(float rgb, float a)					: r(rgb), g(rgb), b(rgb), a(a) {}
		constexpr Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	public:

		// 2�̃J���[�Ԃ̐��`��Ԃ��s���܂�
		static constexpr Color lerp(const Color& value1, const Color& value2, float amount);
		// �l���w�肳�ꂽ�͈͓��ɐ������܂�
		static constexpr Color clamp(const Color& value1, const Color& min, const Color& max);
		// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂�
		static constexpr Color calculateMin(const Color& value1, const Color& value2);
		// ��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂�
		static constexpr Color calculateMax(const Color& value1, const Color& value2);

	public:

		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		// �e�v�f
		float r{ 0.0f };
		float g{ 0.0f };
		float b{ 0.0f };
		float a{ 1.0f };
	};

	// �萔�B
	constexpr Color colorBlack	{ 0.0f, 1.0f };
	constexpr Color colorWhite	{ 1.0f, 1.0f };
	constexpr Color colorRed	{ 1.0f, 0.0f, 0.0f, 1.0f };
	constexpr Color colorGreen	{ 0.0f, 1.0f, 0.0f, 1.0f };
	constexpr Color colorBlue	{ 0.0f, 0.0f, 1.0f, 1.0f };

	// ���Z�q�I�[�o�[���[�h�B
	constexpr Color&	operator += (Color& c1, const Color& c2);
	constexpr Color&	operator -= (Color& c1, const Color& c2);
	constexpr Color&	operator *= (Color& c1, const Color& c2);
	constexpr Color&	operator *= (Color& c, float s);
	constexpr Color&	operator /= (Color& c, float s);
	constexpr Color		operator +  (Color c1, const Color& c2);
	constexpr Color		operator -  (Color c1, const Color& c2);
	constexpr Color		operator *  (Color c1, const Color& c2);
	constexpr Color		operator *  (Color c, float s);
	constexpr Color		operator *  (float s, Color c);
	constexpr Color		operator /  (Color c, float s);
	std::ostream&		operator << (std::ostream& os, const Color& color);

//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// 2�̃J���[�Ԃ̐��`��Ԃ��s���܂�
	inline constexpr Color Color::lerp(const Color& value1, const Color& value2, float amount)
	{
		return {
				helper::lerp(value1.r, value2.r, amount),
				helper::lerp(value1.g, value2.g, amount),
				helper::lerp(value1.b, value2.b, amount),
				helper::lerp(value1.a, value2.a, amount)
		};
	}
	// �l���w�肳�ꂽ�͈͓��ɐ������܂�
	inline constexpr Color Color::clamp(const Color& value1, const Color& min, const Color& max)
	{
		return {
				helper::clamp(value1.r, min.r, max.r),
				helper::clamp(value1.g, min.g, max.g),
				helper::clamp(value1.b, min.b, max.b),
				helper::clamp(value1.a, min.a, max.a)
		};
	}
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂�
	inline constexpr Color Color::calculateMin(const Color& value1, const Color& value2)
	{
		return {
				std::min(value1.r, value2.r),
				std::min(value1.g, value2.g),
				std::min(value1.b, value2.b),
				std::min(value1.a, value2.a)
		};
	}
	// ��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂�
	inline constexpr Color Color::calculateMax(const Color& value1, const Color& value2)
	{
		return {
				std::max(value1.r, value2.r),
				std::max(value1.g, value2.g),
				std::max(value1.b, value2.b),
				std::max(value1.a, value2.a)
		};
	}
	constexpr Color& operator+=(Color& c1, const Color& c2)
	{
		c1.r += c2.r; c1.g += c2.g; c1.b += c2.b; c1.a += c2.a;
		return c1;
	}
	constexpr Color& operator-=(Color& c1, const Color& c2)
	{
		c1.r -= c2.r; c1.g -= c2.g; c1.b -= c2.b; c1.a -= c2.a;
		return c1;
	}
	constexpr Color& operator*=(Color& c1, const Color& c2)
	{
		c1.r *= c2.r; c1.g *= c2.g; c1.b *= c2.b; c1.a *= c2.a;
		return c1;
	}
	constexpr Color& operator*=(Color& c, float s)
	{
		c.r *= s; c.g *= s; c.b *= s; c.a *= s;
		return c;
	}
	constexpr Color& operator/=(Color& c, float s)
	{
		c.r /= s; c.g /= s; c.b /= s; c.a /= s;
		return c;
	}
	constexpr Color operator+(Color c1, const Color& c2)
	{
		return c1 += c2;
	}
	constexpr Color operator-(Color c1, const Color& c2)
	{
		return c1 -= c2;
	}
	constexpr Color operator*(Color c1, const Color& c2)
	{
		return c1 *= c2;
	}
	constexpr Color operator*(Color c, float s)
	{
		return c *= s;
	}
	constexpr Color operator*(float s, Color c)
	{
		return c *= s;
	}
	constexpr Color operator/(Color c, float s)
	{
		return c /= s;
	}
}
#endif