#ifndef DXLIB_3D_POLICY_H_
#define DXLIB_3D_POLICY_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	// Dxlibを使って3Dのプログラムを動かすためのポリシー
	class Dxlib3DPolicy
	{
	public:

		Dxlib3DPolicy(
			const Vector2& gameScreenSize,	// ゲームウィンドウの大きさ
			bool fullScreenFlag,			// フルスクリーンにするか
			float oneMeterDistance,			// ３次元座標系での１メートルの距離
			bool useXAudio					// XAudioを使用するか？
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

		// ３次元座標系での１メートルの距離
		float m_oneMeterDistance;

		// XAudioを使用するか？
		bool m_useXAudio;
	};
}
#endif // !DXLIB_3D_POLICY_H_