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
	// 様々な構造体をDxlib基準に変換する
	class DXConverter
	{
	public:

		// Vector2→VECTORに変換して返す
		static DxLib::VECTOR toVECTOR(const Vector2& v);

		// Vector3→VECTORに変換して返す
		static DxLib::VECTOR toVECTOR(const Vector3& v);

		// VECTOR→Vector3に変換して返す
		static Vector3 toVector3(const DxLib::VECTOR& v);

		// Color→unsigned intに変換して返す（DxlibのGetColor()を呼ぶ）
		static unsigned int toUintColor(const Color& color);

		// Color→COLOR_Fに変換して返す
		static DxLib::COLOR_F toCOLOR_F(const Color& color);

		// Color→COLOR_U8に変換して返す
		static DxLib::COLOR_U8 toCOLOR_U8(const Color& color);

		// COLOR_F→Colorに変換して返す
		static Color toColor(const DxLib::COLOR_F& color_f);

		// Matrix4→MATRIXに変換して返す
		static DxLib::MATRIX toMATRIX(const Matrix4& m);

		// Matrix4→MATRIX_Dに変換して返す
		static DxLib::MATRIX_D toMATRIX_D(const Matrix4& m);

		// MATRIX→Matrix4に変換して返す
		static Matrix4 toMatrix(const DxLib::MATRIX& m);

		// Vertex2dShaderData→VERTEX2DSHADERに変換して返す
		static DxLib::VERTEX2DSHADER toVERTEX2DSHADER(const Vertex2dShaderData& vertex2d);
	};
}
#endif // ! DX_CONVERTER_H_

