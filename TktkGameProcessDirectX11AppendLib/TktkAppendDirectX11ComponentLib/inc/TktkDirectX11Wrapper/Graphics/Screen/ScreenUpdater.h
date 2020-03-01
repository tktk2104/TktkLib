#ifndef SCREEN_UPDATER_H_
#define SCREEN_UPDATER_H_

#include <string>
#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <d3d11.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// 画面の更新、描画を行うクラス
	class ScreenUpdater
	{
	public:

		explicit ScreenUpdater(bool fullScreen);
		~ScreenUpdater();

		ScreenUpdater(const ScreenUpdater& other) = delete;
		ScreenUpdater& operator = (const ScreenUpdater& other) = delete;

	public:

		void start();
		void frameBegin();
		void draw();
		void frameEnd();
		float getDrawPriority();

	public:

		// スワップチェインのポインタを取得する
		IDXGISwapChain* getSwapChainPtr() const;

		// デバイスのポインタを取得する
		ID3D11Device* getDevicePtr() const;

		// デバイスコンテキストのポインタを取得する
		ID3D11DeviceContext* getDeviceContextPtr() const;

		// 画面の背景色を設定する
		void setBackgroundColor(const Color& color);

		// 深度ステンシルビューとレンダーターゲットを設定する
		void setDepthStencilViewAndRenderTargets(int depthStencilViewId, const std::vector<int>& renderTargetIdArray);

	private:

		// スワップチェインのポインタ
		IDXGISwapChain*			m_swapChainPtr;

		// デバイスのポインタ
		ID3D11Device*			m_devicePtr;

		// デバイスコンテキストのポインタ
		ID3D11DeviceContext*	m_deviceContextPtr;

		// メッセージ処理用の変数
		MSG						m_msg{};

		// フルスクリーンフラグ
		bool m_fullScreen{ false };

		// 画面の背景色
		Color m_backGroundColor{ Color::black };
	};
}
#endif // !SCREEN_UPDATER_H_