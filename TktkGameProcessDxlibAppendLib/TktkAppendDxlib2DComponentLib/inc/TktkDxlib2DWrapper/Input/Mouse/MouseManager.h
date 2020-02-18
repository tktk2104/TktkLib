#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include <memory>
#include <TktkMath/Vector2.h>
#include "MouseUpdater.h"
#include "MouseButtonType.h"

namespace tktk
{
	class MouseManager
	{
	public:

		static void setUp();

		static Vector2 getCursorPoint();

		// カーソルの位置を指定座標に移動させる
		static void setCursorPoint(const Vector2& point);

		static void showCursor();

		// ゲームウィンドウの中に限ってマウスカーソルを非表示にする
		static void hideCursor();

		// 引数はInputTypeとMouseButtonTypeの列挙型（ビットフラグ）
		static bool getState(int inputType, int mouseButtonType);

		// 縦方向のマウスホイールの変化量を取得（int）
		static int getVerticalMouseWheel();

		// 縦方向のマウスホイールの変化量を取得（float）
		static float getVerticalMouseWheelF();

		// 横方向のマウスホイールの変化量を取得（int）
		static int getHorizontalMouseWheel();

		// ・横方向のマウスホイールの変化量を取得（float）
		static float getHorizontalMouseWheelF();

	private:

		static std::weak_ptr<MouseUpdater> m_mouseUpdater;
	};
}

#endif // !MOUSE_MANAGER_H_
