#ifndef WINDOW_H_
#define WINDOW_H_

#include <TktkMath/Vector2.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// 「WindowManager」の実装の一部を隠すためのクラス
	class Window
	{
	public:

		// ウィンドウハンドルを取得する
		static HWND getHWND();

		// ウィンドウサイズを取得する
		static const Vector2& getWindowSize();
	};
}
#endif // !WINDOW_H_