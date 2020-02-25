#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include <string>
#include "Asset/PixelShaderData.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// 「PixelShaderManager」の実装の一部を隠すためのクラス
	class PixelShader
	{
	public:

		// 新たなピクセルシェーダーをロードする
		// ※この関数でシェーダーをロードする場合、idは1以上でなければならない
		static void load(int id, int useConstantBufferId, const std::string& fileName);

		// 指定したピクセルシェーダーを削除する
		// ※この関数でシェーダーを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したピクセルシェーダーを管理するクラスの参照を取得する
		static const PixelShaderData& getData(int id);
	};
}
#endif // !PIXEL_SHADER_H_
