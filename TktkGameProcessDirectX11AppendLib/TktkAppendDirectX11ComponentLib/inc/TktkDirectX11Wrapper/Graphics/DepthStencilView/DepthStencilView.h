#ifndef DEPTH_STENCIL_VIEW_H_
#define DEPTH_STENCIL_VIEW_H_

#include "Asset/DepthStencilViewData.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// 「DepthStencilViewManager」の実装の一部を隠すためのクラス
	class DepthStencilView
	{
	public:

		// 新たな深度ビューを作成する
		// ※この関数でビューを作る場合、idは1以上でなければならない
		static void create(int id, const Vector2& useTextureSize);

		// 指定した深度ビューを削除する
		// ※この関数でビューを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した深度ビューを管理するクラスの参照を取得する
		static const DepthStencilViewData& getData(int id);
	};
}
#endif // !DEPTH_STENCIL_VIEW_H_
