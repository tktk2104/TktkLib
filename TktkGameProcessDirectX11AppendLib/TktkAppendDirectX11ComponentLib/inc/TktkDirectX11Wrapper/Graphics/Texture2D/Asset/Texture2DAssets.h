#ifndef TEXTURE_ASSETS_H_
#define TEXTURE_ASSETS_H_

#include <string>
#include <unordered_map>
#include "Texture2DData.h"

namespace tktk
{
	// 「Texture2DData」を管理するクラス
	class Texture2DAssets
	{
	public:

		Texture2DAssets() = default;
		~Texture2DAssets();

		Texture2DAssets(const Texture2DAssets& other) = delete;
		Texture2DAssets& operator = (const Texture2DAssets& other) = delete;

	public:

		// 新たな2Dテクスチャを作成する
		void create(
			int id,
			Texture2DBindFlag bindFlag,
			const std::vector<unsigned char>& textureData,
			unsigned int width,
			unsigned int height,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			Texture2DUsage usage,
			Texture2DCpuAccessFlag cpuAccessFlag,
			bool isCubeMap
		);

		// 新たな2Dテクスチャをロードする
		void load(int id, const std::string& fileName);

		// 指定した2Dテクスチャを削除する
		void erase(int id);

		// 全ての2Dテクスチャを削除する
		void clear();

		// 指定した2Dテクスチャを管理するクラスの参照を取得する
		const Texture2DData& getData(int id);

	private:

		// 2Dテクスチャを管理するクラスの連想配列
		std::unordered_map<int, Texture2DData> m_texture2DAssets;
	};
}
#endif // !TEXTURE_ASSETS_H_