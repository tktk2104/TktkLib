#ifndef DEPTH_STENCIL_H_
#define DEPTH_STENCIL_H_

#include "Asset/DepthStencilData.h"
#include "Asset/SystemDepthStencilId.h"

namespace tktk
{
	// 「DepthStencilManager」の実装の一部を隠すためのクラス
	class DepthStencil
	{
	public:

		// 新たな深度ビューを作成する
		// ※この関数でビューを作る場合、idは1以上でなければならない
		static void create(int id, const Vector2& useTextureSize);

		// 指定した深度ビューを削除する
		// ※この関数でビューを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定した深度ビューを管理するクラスの参照を取得する
		static const DepthStencilData& getData(int id);
	};
}
#endif // !DEPTH_STENCIL_H_
