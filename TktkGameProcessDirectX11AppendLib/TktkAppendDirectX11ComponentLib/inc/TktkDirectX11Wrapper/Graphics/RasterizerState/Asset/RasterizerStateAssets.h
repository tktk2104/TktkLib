#ifndef RASTERIZER_STATE_ASSETS_H_
#define RASTERIZER_STATE_ASSETS_H_

#include <unordered_map>
#include "RasterizerStateData.h"

namespace tktk
{
	// 「RasterizerStateData」を管理するクラス
	class RasterizerStateAssets
	{
	public:

		RasterizerStateAssets() = default;
		~RasterizerStateAssets();

		// コピー禁止
		RasterizerStateAssets(const RasterizerStateAssets& other) = delete;
		RasterizerStateAssets& operator = (const RasterizerStateAssets& other) = delete;
	
	public:

		// 新たなラスタライザステートを作成する
		void create(int id, const D3D11_RASTERIZER_DESC& desc);

		// 指定したラスタライザステートを削除する
		void erase(int id);

		// 全てのラスタライザステートを削除する
		void clear();
	
		// 指定したラスタライザステートを管理するクラスの参照を取得する
		const RasterizerStateData& getData(int id) const;
	
	private:

		// ラスタライザステートを管理するクラスの連想配列
		std::unordered_map<int, RasterizerStateData> m_assets;
	};
}
#endif // !RASTERIZER_STATE_ASSETS_H_