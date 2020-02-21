#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		static MeshAnimatorMaker& makeStart();

	public:

		// 作成する
		MeshAnimator* create();

		// 再生するモーションのID
		MeshAnimatorMaker& motionID(int value);

		// モーションが終了した時ループさせるか？
		MeshAnimatorMaker& isLoop(bool value);

		// モーションの再生速度倍率
		MeshAnimatorMaker& motionSpeedRate(float value);

		// モーション１コマに何秒の時間をかけるか？
		MeshAnimatorMaker& motionIntervalSec(float value);

		// 別ファイルになっているモーションデータを使用するか？
		MeshAnimatorMaker& useOtherMotionData(bool value);

	private:

		// 自身のポインタ
		static MeshAnimatorMaker m_self;

	private:

		int m_motionID{ -1 };
		bool m_isLoop{ false };
		float m_motionSpeedRate{ 1.0f };
		float m_motionIntervalSec{ 1.0f / 60.0f };
		bool m_useOtherMotionData{ false };
	};
}
#endif // !MESH_ANIMATOR_MAKER_H_