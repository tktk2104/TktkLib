#ifndef PIXEL_SHADER_ASSETS_H_
#define PIXEL_SHADER_ASSETS_H_

#include <unordered_map>
#include "PixelShaderData.h"
#include "SystemPixelShaderId.h"

namespace tktk
{
	// 「PixelShaderData」を管理するクラス
	class PixelShaderAssets
	{
	public:

		PixelShaderAssets() = default;
		~PixelShaderAssets();

		PixelShaderAssets(const PixelShaderAssets& other) = delete;
		PixelShaderAssets& operator = (const PixelShaderAssets& other) = delete;

	public:

		// 新たなピクセルシェーダーをロードする
		void load(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName);

		// 指定したピクセルシェーダーを削除する
		void erase(int id);

		// 全てのピクセルシェーダーを削除する
		void clear();

		// 指定したピクセルシェーダーを管理するクラスの参照を取得する
		const PixelShaderData& getData(int id) const;

	private:

		// ピクセルシェーダーを管理するクラスの連想配列
		std::unordered_map<int, PixelShaderData> m_assets;
	};
}
#endif // !PIXEL_SHADER_ASSETS_H_