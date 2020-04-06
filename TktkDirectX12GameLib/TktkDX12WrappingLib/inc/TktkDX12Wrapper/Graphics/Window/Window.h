#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <TktkMath/Structs/Vector2.h>
#include <Windows.h>
#undef min
#undef max
#include "WindowInitParam.h"

namespace tktk
{
	class Window
	{
	public:

		explicit Window(
			WindowInitParam&& initParam
		);

		Window(const Window& other) = delete;
		Window& operator = (const Window& other) = delete;

	public:

		// ウィンドウハンドルを取得する
		HWND getHWND() const;

		// ウィンドウサイズを取得する
		const tktkMath::Vector2& getWindowSize() const;

	private:

		// ウィンドウハンドル
		HWND m_hwnd{ nullptr };

		// ウィンドウサイズ
		tktkMath::Vector2 m_windowSize{ };
	};
}
#endif // !WINDOW_H_