#ifndef WINDOW_UPDATER_H_
#define WINDOW_UPDATER_H_

#include <string>
#include <TktkMath/Vector2.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// ウィンドウの表示を行うクラス
	class WindowUpdater
	{
	public:

		WindowUpdater(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string& windowName,
			const Vector2& windowSize
		);
		~WindowUpdater();

		WindowUpdater(const WindowUpdater& other) = delete;
		WindowUpdater& operator = (const WindowUpdater& other) = delete;

	public:

		// ウィンドウハンドルを取得する
		HWND getHWND() const;

		// ウィンドウサイズを取得する
		const Vector2& getWindowSize() const;

	private:

		// ウィンドウハンドル
		HWND m_hwnd;

		// ウィンドウサイズ
		Vector2 m_windowSize;
	};
}
#endif // !WINDOW_UPDATER_H_