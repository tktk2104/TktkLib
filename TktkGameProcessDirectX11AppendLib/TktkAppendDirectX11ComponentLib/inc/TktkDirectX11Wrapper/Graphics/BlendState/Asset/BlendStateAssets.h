#ifndef BLEND_STATE_ASSETS_H_
#define BLEND_STATE_ASSETS_H_

#include <unordered_map>
#include "BlendStateData.h"

namespace tktk
{
	class BlendStateAssets
	{
	public:

		BlendStateAssets() = default;
		~BlendStateAssets();

		// コピー禁止
		BlendStateAssets(const BlendStateAssets& other) = delete;
		BlendStateAssets& operator = (const BlendStateAssets& other) = delete;

	public:

		// 新たなブレンドステートを作成する
		void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// 指定したブレンドステートを削除する
		void erase(int id);

		// 全てのブレンドステートを削除する
		void clear();

		// 指定したブレンドステートを管理するクラスのポインタを取得する
		BlendStateData* getDataPtr(int id);

	private:

		// ブレンドステートを管理するクラスの連想配列
		std::unordered_map<int, BlendStateData> m_assets;
	};
}
#endif // !BLEND_STATE_ASSETS_H_