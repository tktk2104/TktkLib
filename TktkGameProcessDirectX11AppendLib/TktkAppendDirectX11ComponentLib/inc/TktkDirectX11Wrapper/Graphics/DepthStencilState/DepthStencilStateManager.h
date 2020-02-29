#ifndef DEPTH_STENCIL_STATE_MANAGER_H_
#define DEPTH_STENCIL_STATE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilStateAssets.h"

namespace tktk
{
	class DepthStencilStateManager
	{
	public:

		// 「DepthStencilStateAssets」を生成
		static void setUp();

	public:

		// 新たな深度ステンシルステートを作成する
		static void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// 指定した深度ステンシルステートを削除する
		static void erase(int id);

		// 全ての深度ステンシルステートを削除する
		static void clear();

		// 指定した深度ステンシルステートを管理するクラスのポインタを取得する
		static DepthStencilStateData* getData(int id);

	private:

		static CfpPtr<DepthStencilStateAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_STATE_MANAGER_H_