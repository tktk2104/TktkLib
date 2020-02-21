#ifndef SCREEN_UPDATER_H_
#define SCREEN_UPDATER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include "../RenderTarget/RenderTargetUpdater.h"

namespace tktk
{
	class ScreenUpdater
	{
	public:

		ScreenUpdater(
			const Vector2& gameScreenSize,
			bool fullScreen
		);

	public:

		void awake();
		void start();
		void onDestroy();
		void update();
		void draw();
		void frameEnd();
		float getUpdatePriority();
		float getDrawPriority();

	public:

		// ディスプレイの大きさを取得
		const Vector2& getDisplaySize() const;

		// ゲームスクリーンの大きさを取得
		const Vector2& getGameScreenSize() const;

		// レターボックス（フルスクリーン時の画面の余白のサイズ）の大きさを取得
		const Vector2& getLetterBoxSize() const;

		// 画面の背景色を設定する
		void backgroundColor(const Color& color);

	private:

		void calculateLetterBoxSize();

	private:

		// ディスプレイの大きさ
		Vector2 m_displaySize;
		// ゲームスクリーンの大きさ
		Vector2 m_gameScreenSize;
		// レターボックス（フルスクリーン時の画面の余白のサイズ）の大きさ
		Vector2 m_letterBoxSize{ Vector2::zero };

		bool m_fullScreen;
	};
}
#endif // !SCREEN_UPDATER_H_
