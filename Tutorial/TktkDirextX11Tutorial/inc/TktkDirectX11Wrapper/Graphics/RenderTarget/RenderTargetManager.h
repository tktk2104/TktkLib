#ifndef RENDER_TARGET_MANAGER_H_
#define RENDER_TARGET_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/RenderTargetAssets.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// 「RenderTargetAssets」に簡単にアクセスするためのクラス
	class RenderTargetManager
	{
	public:

		// 「RenderTargetAssets」を生成
		static void setUp();

	public:

		// 新たなレンダーターゲットを生成する
		static void create(int id, ID3D11Texture2D* renderTargetTexture);

		// 指定したレンダーターゲットを削除する
		static void erase(int id);

		// 全てのレンダーターゲットを削除する
		static void clear();

		// 指定したレンダーターゲットを管理するクラスの参照を取得する
		static const RenderTargetData& getData(int id);

	private:

		static CfpPtr<RenderTargetAssets> m_assetsPtr;
	};
}
#endif // !RENDER_TARGET_MANAGER_H_