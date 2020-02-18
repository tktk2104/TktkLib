#ifndef SCREEN_H_
#define SCREEN_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	class Screen
	{
	public:

		// ディスプレイの大きさを取得
		static const Vector2& getDisplaySize();

		// ゲームスクリーンの大きさを取得
		static const Vector2& getGameScreenSize();

		// レターボックス（フルスクリーン時の画面の余白のサイズ）の大きさを取得
		static const Vector2& getLetterBoxSize();

		// 画面の背景色を設定する
		static void backgroundColor(const Color& color);
	};
}
#endif // !SCREEN_H_