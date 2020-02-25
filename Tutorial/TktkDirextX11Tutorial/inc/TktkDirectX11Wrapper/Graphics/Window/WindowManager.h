#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "WindowUpdater.h"

namespace tktk
{
	// 「WindowUpdater」に簡単にアクセスするためのクラス
	class WindowManager
	{
	public:

		// 「WindowUpdater」を生成
		static void setUp(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string& windowName,
			const Vector2& windowSize
		);

	public:

		// ウィンドウハンドルを取得する
		static HWND getHWND();

		// ウィンドウサイズを取得する
		static const Vector2& getWindowSize();

	private:

		static CfpPtr<WindowUpdater> m_updaterPtr;
	};
}
#endif // !WINDOW_MANAGER_H_