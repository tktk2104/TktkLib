#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

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

	private:

		static CfpPtr<ScreenUpdater> m_updaterPtr;
	};
}
#endif // !SCREEN_MANAGER_H_
