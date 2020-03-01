#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ScreenUpdater.h"

namespace tktk
{
	// 「ScreenUpdater」に簡単にアクセスするためのクラス
	class ScreenManager
	{
	public:

		// 「ScreenUpdater」を生成
		static void setUp(bool fullScreen);

	public:

		// スワップチェインのポインタを取得する
		static IDXGISwapChain* getSwapChainPtr();

		// デバイスのポインタを取得する
		static ID3D11Device* getDevicePtr();

		// デバイスコンテキストのポインタを取得する
		static ID3D11DeviceContext* getDeviceContextPtr();

		// 画面の背景色を設定する
		static void setBackgroundColor(const Color& color);

		// 深度ステンシルビューとレンダーターゲットを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class DepthStencilViewIdType, class... RenderTargetIdType, std::enable_if_t<is_idType_v<DepthStencilViewIdType> && is_idType_all_v<RenderTargetIdType...>>* = nullptr>
		static void setDepthStencilViewAndRenderTargets(DepthStencilViewIdType depthStencilViewId, RenderTargetIdType... renderTargetIds)
		{
			setDepthStencilViewAndRenderTargetsImpl(static_cast<int>(depthStencilViewId), { static_cast<int>(renderTargetIds)... });
		}
		template <class DepthStencilViewIdType, class... RenderTargetIdType, std::enable_if_t<!(is_idType_v<DepthStencilViewIdType> && is_idType_all_v<RenderTargetIdType...>)>* = nullptr>
		static void setDepthStencilViewAndRenderTargets(DepthStencilViewIdType depthStencilViewId, RenderTargetIdType... renderTargetIds)
		{
			static_assert(false, "Id Fraud Type");
		}

		// setDepthStencilViewAndRenderTargets()の実装
		static void setDepthStencilViewAndRenderTargetsImpl(int depthStencilViewId, const std::vector<int>& renderTargetIdArray);

	private:

		static CfpPtr<ScreenUpdater> m_updaterPtr;
	};
}
#endif // !SCREEN_MANAGER_H_
