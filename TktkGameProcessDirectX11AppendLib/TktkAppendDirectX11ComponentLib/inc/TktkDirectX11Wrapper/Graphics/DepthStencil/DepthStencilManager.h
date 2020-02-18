#ifndef DEPTH_STENCIL_MANAGER_H_
#define DEPTH_STENCIL_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilAssets.h"
#include "Asset/SystemDepthStencilId.h"

namespace tktk
{
	// 「DepthStencilAssets」に簡単にアクセスするためのクラス
	class DepthStencilManager
	{
	public:

		// 「DepthStencilAssets」を生成
		static void setUp();

	public:

		// 新たな深度ビューを作成する
		static void create(int id, const Vector2& useTextureSize);

		// 指定した深度ビューを削除する
		static void erase(int id);

		// 全ての深度ビューを削除する
		static void clear();

		// 指定した深度ビューを管理するクラスの参照を取得する
		static const DepthStencilData& getData(int id);

	private:

		static CfpPtr<DepthStencilAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_MANAGER_H_
