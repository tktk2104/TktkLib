#ifndef MOUSE_H_
#define MOUSE_H_

#include <TktkMath/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	// 「MouseManager」の実装の一部を隠すためのクラス
	class Mouse
	{
	public:

		// 指定のボタンが押されているかを判定
		static bool isPush(MouseButtonType button);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType button);

		// マウスカーソルの座標を取得する
		static Vector2 mousePos();
	};
}
#endif // !MOUSE_H_