#ifndef DX_CONVERTER_H_
#define DX_CONVERTER_H_

#include <DxLib.h>

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Color.h>
#include <TktkMath/Matrix4.h>
#include "../DxlibStructWrapper/Vertex2dShaderData.h"

namespace tktk
{
	// �l�X�ȍ\���̂�Dxlib��ɕϊ�����
	class DXConverter
	{
	public:

		// Vector2��VECTOR�ɕϊ����ĕԂ�
		static DxLib::VECTOR toVECTOR(const Vector2& v);

		// Vector3��VECTOR�ɕϊ����ĕԂ�
		static DxLib::VECTOR toVECTOR(const Vector3& v);

		// VECTOR��Vector3�ɕϊ����ĕԂ�
		static Vector3 toVector3(const DxLib::VECTOR& v);

		// Color��unsigned int�ɕϊ����ĕԂ��iDxlib��GetColor()���Ăԁj
		static unsigned int toUintColor(const Color& color);

		// Color��COLOR_F�ɕϊ����ĕԂ�
		static DxLib::COLOR_F toCOLOR_F(const Color& color);

		// Color��COLOR_U8�ɕϊ����ĕԂ�
		static DxLib::COLOR_U8 toCOLOR_U8(const Color& color);

		// COLOR_F��Color�ɕϊ����ĕԂ�
		static Color toColor(const DxLib::COLOR_F& color_f);

		// Matrix4��MATRIX�ɕϊ����ĕԂ�
		static DxLib::MATRIX toMATRIX(const Matrix4& m);

		// Matrix4��MATRIX_D�ɕϊ����ĕԂ�
		static DxLib::MATRIX_D toMATRIX_D(const Matrix4& m);

		// MATRIX��Matrix4�ɕϊ����ĕԂ�
		static Matrix4 toMatrix(const DxLib::MATRIX& m);

		// Vertex2dShaderData��VERTEX2DSHADER�ɕϊ����ĕԂ�
		static DxLib::VERTEX2DSHADER toVERTEX2DSHADER(const Vertex2dShaderData& vertex2d);
	};
}
#endif // ! DX_CONVERTER_H_

