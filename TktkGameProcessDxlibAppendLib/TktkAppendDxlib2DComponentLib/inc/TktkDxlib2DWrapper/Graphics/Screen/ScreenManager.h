#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ScreenUpdater.h"

namespace tktk
{
	class ScreenManager
	{
	public:

		static void setUp(
			const Vector2& gameScreenSize,
			bool fullScreen
		);

		// ディスプレイの大きさを取得
		static const Vector2& getDisplaySize();

		// ゲームスクリーンの大きさを取得
		static const Vector2& getGameScreenSize();

		// レターボックス（フルスクリーン時の画面の余白のサイズ）の大きさを取得
		static const Vector2& getLetterBoxSize();

		// 画面の背景色を設定する
		static void backgroundColor(const Color& color);

	private:

		static CfpPtr<ScreenUpdater> m_screenUpdater;
	};
}
#endif // !SCREEN_MANAGER_H_