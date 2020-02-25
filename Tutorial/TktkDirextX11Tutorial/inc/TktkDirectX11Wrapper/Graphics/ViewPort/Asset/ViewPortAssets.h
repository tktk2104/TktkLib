#ifndef VIEW_PORT_ASSETS_H_
#define VIEW_PORT_ASSETS_H_

#include <unordered_map>
#include "ViewPortData.h"

namespace tktk
{
	class ViewPortAssets
	{
	public:

		ViewPortAssets();
		~ViewPortAssets();

		ViewPortAssets(const ViewPortAssets& other) = delete;
		ViewPortAssets& operator = (const ViewPortAssets& other) = delete;

	public:

		// 新たなビューポートを生成する
		void create(int id, const Vector2& position, const Vector2& size);

		// 指定したビューポートを削除する
		void erase(int id);

		// 全てのビューポートを削除する
		void clear();

		// 指定したビューポートを管理するクラスの参照を取得する
		const ViewPortData& getData(int id) const;

	private:

		// ビューポートを管理するクラスの連想配列
		std::unordered_map<int, ViewPortData> m_assets;
	};
}
#endif // !VIEW_PORT_ASSETS_H_