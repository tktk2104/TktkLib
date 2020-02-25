#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		// インスタンス作成開始
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<MeshAnimator> create();

		MeshAnimatorMaker& meshDrawer(CfpPtr<MeshDrawer> value);

		MeshAnimatorMaker& animationId(int value);

		MeshAnimatorMaker& animFrameIntervalPerSec(float value);

		MeshAnimatorMaker& animSpeedRate(float value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static MeshAnimatorMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		CfpPtr<MeshDrawer> m_meshDrawer{};
		int m_animationId{ 0 };
		float m_animFrameIntervalPerSec{ 60.0f };
		float m_animSpeedRate{ 1.0f };
	};
}

#endif // !MESH_ANIMATOR_MAKER_H_