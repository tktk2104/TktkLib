#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/PixelShaderAssets.h"

namespace tktk
{
	// 「PixelShaderAssets」に簡単にアクセスするためのクラス
	class PixelShaderManager
	{
	public:

		// 「PixelShaderAssets」を生成
		static void setUp();

	public:

		// 新たなピクセルシェーダーをロードする
		static void load(int id, int useConstantBufferId, const std::string& fileName);

		// 指定したピクセルシェーダーを削除する
		static void erase(int id);

		// 全てのピクセルシェーダーを削除する
		static void clear();

		// 指定したピクセルシェーダーを管理するクラスの参照を取得する
		static const PixelShaderData& getData(int id);

	private:

		static CfpPtr<PixelShaderAssets> m_assetsPtr;
	};
}
#endif // !PIXEL_SHADER_MANAGER_H_