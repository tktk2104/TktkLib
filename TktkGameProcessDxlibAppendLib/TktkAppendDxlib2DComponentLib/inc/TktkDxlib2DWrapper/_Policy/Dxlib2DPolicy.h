#ifndef DXLIB_2D_POLICY_H_
#define DXLIB_2D_POLICY_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	// Dxlibを使って2Dのプログラムを動かすためのポリシー
	class Dxlib2DPolicy
	{
	public:

		Dxlib2DPolicy(
			const Vector2& gameScreenSize,	// ゲームウィンドウの大きさ
			bool fullScreenFlag				// フルスクリーンにするか
		);

	public:

		void awake();
		bool isDestroy() const;

	private:

		void setUpdatePriority();

	private:

		// ゲーム画面の大きさ
		Vector2 m_gameScreenSize;

		// フルスクリーンフラグ
		bool m_fullScreenFlag;
	};
}

#endif // !DXLIB_2D_POLICY_H_

