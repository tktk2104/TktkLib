#ifndef SCREEN_H_
#define SCREEN_H_

#include <vector>
#include <d3d11.h>
#include <TktkMath/Color.h>

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

		// レンダーターゲットと深度ステンシルビューを設定する
		static void setRenderTargetsAndDepthStencilView(const std::vector<int>& renderTargetIdArray, int depthStencilViewId);
	};
}
#endif // !SCREEN_H_
