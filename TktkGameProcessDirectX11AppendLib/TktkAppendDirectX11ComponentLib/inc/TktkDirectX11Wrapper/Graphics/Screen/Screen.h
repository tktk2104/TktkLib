#ifndef SCREEN_H_
#define SCREEN_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <d3d11.h>

namespace tktk
{
	// 「ScreenManager」の実装の一部を隠すためのクラス
	class Screen
	{
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

		// ビューポートを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void setViewport(IdType viewPortId)
		{
			setViewportImpl(static_cast<int>(viewPortId));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void setViewport(IdType viewPortId) { static_assert(false, "ViewportId Fraud Type"); }

	private:

		// setDepthStencilViewAndRenderTargets()の実装
		static void setDepthStencilViewAndRenderTargetsImpl(int depthStencilViewId, const std::vector<int>& renderTargetIdArray);
	
		// setViewport()の実装
		static void setViewportImpl(int viewPortId);
	};
}
#endif // !SCREEN_H_
