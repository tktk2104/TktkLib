#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "MouseUpdater.h"
#include "MouseButtonType.h"

namespace tktk
{
	// 「MouseUpdater」に簡単にアクセスするためのクラス
	class MouseManager
	{
	public:

		// 「MouseUpdater」を生成
		static void setUp();

	public:

		// 指定のボタンが押されているかを判定
		static bool isPush(MouseButtonType button);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType button);

		// マウスカーソルの座標を取得する
		static Vector2 mousePos();

	private:

		static CfpPtr<MouseUpdater> m_updaterPtr;
	};
}
#endif // !MOUSE_MANAGER_H_