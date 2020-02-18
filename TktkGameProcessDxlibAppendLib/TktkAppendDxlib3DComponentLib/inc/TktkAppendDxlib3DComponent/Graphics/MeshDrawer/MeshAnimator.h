#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "MeshDrawer.h"

namespace tktk
{
	// 「MeshDrawer」で描画したメッシュをアニメーションさせるコンポーネント
	// 【前提コンポーネント：MeshDrawer】
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(
			int motionID,				// 再生するモーションのID
			bool isLoop,				// モーションが終了した時ループさせるか？
			float motionSpeedRate,		// モーションの再生速度倍率
			float motionIntervalSec,	// モーション１コマに何秒の時間をかけるか？
			bool useOtherMotionData		// 別ファイルになっているモーションデータを使用するか？
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// モーションを変更
		void changeMotion(
			int motionID,			// 再生するモーションのID
			bool isLoop,			// モーションが終了した時ループさせるか？
			float lerpTimeSec,		// モーション遷移の補完を何秒かけるか？
			bool useOtherMotionData	// 別ファイルになっているモーションデータを使用するか？
		);

		// 再生しているモーション番号を取得
		int getCurMotionID() const;

		// モーションが終了したかを取得
		bool isEndAnimation() const;

		// 再生しているモーションが何秒間の長さを持つかを取得
		float getCurMotionEndTime() const;

		// モーションの再生速度倍率を取得
		float getMotionSpeedRate() const;

		// モーションの再生速度倍率を再設定
		void setMotionSpeedRate(float speed);

	private:

		std::weak_ptr<MeshDrawer> m_meshDrawer;

		// 別ファイルになっているモーションを現在使用しているか
		bool m_curUseOtherMotionData;

		// 別ファイルになっているモーションを１つ前に使用していたか
		bool m_preUseOtherMotionData;

		// 現在のモーションのID
		int m_curMotionID;

		// １つ前のモーションのID
		int m_preMotionID;

		// モーションをループさせるか
		bool m_isLoop;

		// モーションのスピード（倍率）
		float m_motionSpeedRate;

		// アニメーション１コマにかける時間（秒）
		float m_motionIntervalSec;

		// 現在のモーションのタイマー
		float m_curMotionTimer{ 0.0f };

		// 1つ前のモーションのタイマー
		float m_preMotionTimer{ 0.0f };

		// モーション補完タイマー
		float m_lerpSecTimer{ 0.0f };

		// モーション補完時間
		float m_lerpTimeSec{ 0.1f };
	};
}
#endif // !MESH_ANIMATOR_H_