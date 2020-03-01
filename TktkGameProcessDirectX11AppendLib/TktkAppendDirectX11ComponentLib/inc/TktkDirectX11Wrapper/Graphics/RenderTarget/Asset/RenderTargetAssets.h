#ifndef RENDER_TARGET_ASSETS_H_
#define RENDER_TARGET_ASSETS_H_

#include <unordered_map>
#include "RenderTargetData.h"

namespace tktk
{
	// 「RenderTargetData」を管理するクラス
	class RenderTargetAssets
	{
	public:

		RenderTargetAssets() = default;
		~RenderTargetAssets();

		RenderTargetAssets(const RenderTargetAssets& other) = delete;
		RenderTargetAssets& operator = (const RenderTargetAssets& other) = delete;

	public:

		// 新たなレンダーターゲットを生成する
		void create(int id, ID3D11Texture2D* renderTargetTexture);

		// 指定したレンダーターゲットを削除する
		void erase(int id);

		// 全てのレンダーターゲットを削除する
		void clear();

		// 指定したレンダーターゲットを管理するクラスの参照を取得する
		const RenderTargetData& getData(int id) const;

	private:

		// レンダーターゲットを管理するクラスの連想配列
		std::unordered_map<int, RenderTargetData> m_assets;
	};
}
#endif // !RENDER_TARGET_ASSETS_H_