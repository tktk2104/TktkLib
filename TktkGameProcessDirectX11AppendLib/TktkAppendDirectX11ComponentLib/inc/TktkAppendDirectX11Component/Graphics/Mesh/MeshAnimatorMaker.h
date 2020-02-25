#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<MeshAnimator> create();

		MeshAnimatorMaker& meshDrawer(CfpPtr<MeshDrawer> value);

		MeshAnimatorMaker& animationId(int value);

		MeshAnimatorMaker& animFrameIntervalPerSec(float value);

		MeshAnimatorMaker& animSpeedRate(float value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static MeshAnimatorMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		CfpPtr<MeshDrawer> m_meshDrawer{};
		int m_animationId{ 0 };
		float m_animFrameIntervalPerSec{ 60.0f };
		float m_animSpeedRate{ 1.0f };
	};
}

#endif // !MESH_ANIMATOR_MAKER_H_