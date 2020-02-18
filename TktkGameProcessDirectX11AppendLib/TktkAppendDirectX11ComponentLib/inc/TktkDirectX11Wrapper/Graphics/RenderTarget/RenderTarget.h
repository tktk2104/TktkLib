#ifndef RENDER_TARGET_H_
#define RENDER_TARGET_H_

#include "Asset/RenderTargetData.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// 「RenderTargetManager」の実装の一部を隠すためのクラス
	class RenderTarget
	{
	public:

		// 新たなレンダーターゲットを生成する
		// ※この関数でレンダーターゲットを作る場合、idは1以上でなければならない
		static void create(int id, ID3D11Texture2D* renderTargetTexture);

		// 指定したレンダーターゲットを削除する
		// ※この関数でレンダーターゲットを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したレンダーターゲットを管理するクラスの参照を取得する
		static const RenderTargetData& getData(int id);
	};
}
#endif // !RENDER_TARGET_H_