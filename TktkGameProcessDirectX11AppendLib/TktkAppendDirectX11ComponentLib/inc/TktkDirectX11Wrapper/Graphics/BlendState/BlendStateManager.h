#ifndef BLEND_STATE_MANAGER_H_
#define BLEND_STATE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/BlendStateAssets.h"

namespace tktk
{
	class BlendStateManager
	{
	public:

		// 「BlendStateAssets」を作成
		static void setUp();

	public:

		// 新たなブレンドステートを作成する
		static void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// 指定したブレンドステートを削除する
		static void erase(int id);

		// 全てのブレンドステートを削除する
		static void clear();

		// 指定したブレンドステートを管理するクラスのポインタを取得する
		static BlendStateData* getDataPtr(int id);

	private:

		static CfpPtr<BlendStateAssets> m_assetsPtr;
	};
}
#endif // !BLEND_STATE_MANAGER_H_