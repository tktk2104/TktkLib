#ifndef DEPTH_STENCIL_ASSETS_H_
#define DEPTH_STENCIL_ASSETS_H_

#include <unordered_map>
#include "DepthStencilData.h"

namespace tktk
{
	// 「DepthStencilData」を管理するクラス
	class DepthStencilAssets
	{
	public:

		DepthStencilAssets();
		~DepthStencilAssets();

		DepthStencilAssets(const DepthStencilAssets& other) = delete;
		DepthStencilAssets& operator = (const DepthStencilAssets& other) = delete;

	public:

		// 新たな深度ビューを作成する
		void create(int id, const Vector2& useTextureSize);

		// 指定した深度ビューを削除する
		void erase(int id);

		// 全ての深度ビューを削除する
		void clear();

		// 指定した深度ビューを管理するクラスの参照を取得する
		const DepthStencilData& getData(int id) const;

	private:

		// 深度ビューを管理するクラスの連想配列
		std::unordered_map<int, DepthStencilData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_ASSETS_H_