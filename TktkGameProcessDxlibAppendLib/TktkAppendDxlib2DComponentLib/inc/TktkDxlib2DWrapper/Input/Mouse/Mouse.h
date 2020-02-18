#ifndef MOUSE_H_
#define MOUSE_H_

#include <TktkMath/Vector2.h>
#include "../InputType.h"
#include "MouseButtonType.h"

namespace tktk
{
	class Mouse
	{
	public:

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
	};
}

#endif // !MOUSE_H_