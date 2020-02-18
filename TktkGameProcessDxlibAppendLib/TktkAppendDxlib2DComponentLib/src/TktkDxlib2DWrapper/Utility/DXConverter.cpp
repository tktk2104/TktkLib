#include "TktkDxlib2DWrapper/Utility/DXConverter.h"

namespace tktk
{
	DxLib::VECTOR DXConverter::toVECTOR(const Vector2 & v)
	{
		return DxLib::VGet(v.x, v.y, 0.0f);
	}

	DxLib::VECTOR DXConverter::toVECTOR(const Vector3 & v)
	{
		return DxLib::VGet(v.x, v.y, v.z);
	}

	Vector3 DXConverter::toVector3(const DxLib::VECTOR & v)
	{
		return Vector3(v.x, v.y, v.z);
	}

	unsigned int DXConverter::toUintColor(const Color & color)
	{
		return DxLib::GetColor(
			static_cast<int>(color.r) * 255,
			static_cast<int>(color.g) * 255,
			static_cast<int>(color.b) * 255
		);
	}

	DxLib::COLOR_F DXConverter::toCOLOR_F(const Color & color)
	{
		return DxLib::GetColorF(color.r, color.g, color.b, color.a);
	}

	DxLib::COLOR_U8 DXConverter::toCOLOR_U8(const Color & color)
	{
		return DxLib::GetColorU8(
			static_cast<int>(color.r),
			static_cast<int>(color.g),
			static_cast<int>(color.b),
			static_cast<int>(color.a)
		);
	}

	Color DXConverter::toColor(const DxLib::COLOR_F & color_f)
	{
		return Color(color_f.r, color_f.g, color_f.b, color_f.a);
	}

	DxLib::MATRIX DXConverter::toMATRIX(const Matrix4 & m)
	{
		DxLib::MATRIX result;

		memcpy(&result, &m, sizeof(DxLib::MATRIX));

		return result;
	}

	DxLib::MATRIX_D DXConverter::toMATRIX_D(const Matrix4 & m)
	{
		DxLib::MATRIX_D result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] = m.m[i][j];
			}
		}
		return result;
	}

	Matrix4 DXConverter::toMatrix(const DxLib::MATRIX & m)
	{
		Matrix4 result;

		memcpy(&result, &m, sizeof(Matrix4));

		return result;
	}

	DxLib::VERTEX2DSHADER DXConverter::toVERTEX2DSHADER(const Vertex2dShaderData & vertex2d)
	{
		return {
			toVECTOR(vertex2d.pos),
			vertex2d.rhw,
			toCOLOR_U8(vertex2d.dif),
			toCOLOR_U8(vertex2d.spc),
			vertex2d.uv.x,
			vertex2d.uv.y,
			vertex2d.suv.x,
			vertex2d.suv.y
		};
	}
}