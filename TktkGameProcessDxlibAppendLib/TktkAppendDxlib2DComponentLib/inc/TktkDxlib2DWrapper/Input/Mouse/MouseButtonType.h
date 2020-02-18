#ifndef MOUSE_BUTTON_TYPE_H_
#define MOUSE_BUTTON_TYPE_H_

namespace tktk
{
	// マウスのボタンの種類
	enum MouseButtonType
	{
		MOUSE_LEFT_BUTTON	= 1 << 0,	// 左マウスボタン
		MOUSE_RIGHT_BUTTON	= 1 << 1,	// 右マウスボタン
		MOUSE_MIDDLE_BUTTON = 1 << 2	// マウスホイール押し込み
	};
}
#endif // !MOUSE_BUTTON_TYPE_H_