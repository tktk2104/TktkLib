#ifndef COLOR_H_
#define COLOR_H_

#include <ostream>
#include <string>

struct Color
{
public:

	Color() = default;
	Color(float r, float g, float b, float a);

	// Color(0, 0, 0, 1)
	static const Color black;
	// Color(1, 1, 1, 1)
	static const Color white;
	// Color(1, 0, 0, 1)
	static const Color red;
	// Color(0, 1, 0, 1)
	static const Color green;
	// Color(0, 0, 1, 1)
	static const Color blue;

	// 2�̃J���[�Ԃ̐��`��Ԃ��s���܂�
	static Color lerp(const Color& value1, const Color& value2, float amount);
	//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
	static Color clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color(1.0f, 1.0f, 1.0f, 1.0f));
	// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂�
	static Color calculateMin(const Color& value1, const Color& value2);
	// ��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂�
	static Color calculateMax(const Color& value1, const Color& value2);

	// �t�H�[�}�b�g���ꂽ������ɕϊ�
	std::string toString() const;

public:

	float r { 0.0f };
	float g { 0.0f };
	float b { 0.0f };
	float a { 1.0f };
};

Color& operator += (Color& c1, const Color& c2);
Color& operator -= (Color& c1, const Color& c2);
Color& operator *= (Color& c1, const Color& c2);
Color& operator *= (Color& c, float s);
Color& operator /= (Color& c, float s);

Color operator + (Color c1, const Color& c2);
Color operator - (Color c1, const Color& c2);
Color operator * (Color c1, const Color& c2);
Color operator * (Color c, float s);
Color operator * (float s, Color c);
Color operator / (Color c, float s);

std::ostream& operator<<(std::ostream& os, const Color& color);
#endif