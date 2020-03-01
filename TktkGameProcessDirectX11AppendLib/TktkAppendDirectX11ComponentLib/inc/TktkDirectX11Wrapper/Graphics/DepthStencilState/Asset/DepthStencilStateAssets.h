#ifndef DEPTH_STENCIL_STATE_ASSETS_H_
#define DEPTH_STENCIL_STATE_ASSETS_H_

#include <unordered_map>
#include "DepthStencilStateData.h"

namespace tktk
{
	class DepthStencilStateAssets
	{
	public:

		DepthStencilStateAssets() = default;
		~DepthStencilStateAssets();

		// コピー禁止
		DepthStencilStateAssets(const DepthStencilStateAssets& other) = delete;
		DepthStencilStateAssets& operator = (const DepthStencilStateAssets& other) = delete;

	public:

		// 新たな深度ステンシルステートを作成する
		void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// 指定した深度ステンシルステートを削除する
		void erase(int id);

		// 全ての深度ステンシルステートを削除する
		void clear();

		// 指定した深度ステンシルステートを管理するクラスのポインタを取得する
		DepthStencilStateData* getDataPtr(int id);

	private:

		std::unordered_map<int, DepthStencilStateData> m_assets;
	};
}
#endif // !DEPTH_STENCIL_STATE_ASSETS_H_