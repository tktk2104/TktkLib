#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	class MouseUpdater
	{
	public:

		MouseUpdater() = default;

	public:

		void update();

	public:

		Vector2 getCursorPoint();

		// カーソルの位置を指定座標に移動させる
		void setCursorPoint(const Vector2& point);

		void showCursor();

		// ゲームウィンドウの中に限ってマウスカーソルを非表示にする
		void hideCursor();

		// 引数はInputTypeとMouseButtonTypeの列挙型（ビットフラグ）
		bool getState(int inputType, int mouseButtonType);

		// 縦方向のマウスホイールの変化量を取得（int）
		int getVerticalMouseWheel();

		// 縦方向のマウスホイールの変化量を取得（float）
		float getVerticalMouseWheelF();

		// 横方向のマウスホイールの変化量を取得（int）
		int getHorizontalMouseWheel();

		// ・横方向のマウスホイールの変化量を取得（float）
		float getHorizontalMouseWheelF();

	private:

		int m_curState;

		int m_preState;
	};
}
#endif // !MOUSE_UPDATER_H_
