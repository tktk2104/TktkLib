#ifndef DEPTH_STENCIL_VIEW_ASSETS_H_
#define DEPTH_STENCIL_VIEW_ASSETS_H_

#include <unordered_map>
#include "DepthStencilViewData.h"

namespace tktk
{
	// 「DepthStencilViewData」を管理するクラス
	class DepthStencilViewAssets
	{
	public:

		DepthStencilViewAssets() = default;
		~DepthStencilViewAssets();

		DepthStencilViewAssets(const DepthStencilViewAssets& other) = delete;
		DepthStencilViewAssets& operator = (const DepthStencilViewAssets& other) = delete;

	public:

		// 新たな深度ビューを作成する
		void create(int id, const Vector2& useTextureSize);

		// 指定した深度ビューを削除する
		void erase(int id);

		// 全ての深度ビューを削除する
		void clear();

		// 指定した深度ビューを管理するクラスの参照を取得する
		const DepthStencilViewData& getData(int id) const;

	private:

		// 深度ビューを管理するクラスの連想配列
		std::unordered_map<int, DepthStencilViewData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_VIEW_ASSETS_H_