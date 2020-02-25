#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "MeshAnimator.h"

namespace tktk
{
	class MeshAnimatorMaker
	{
	public:

		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<MeshAnimator> create();

		// �Đ����郂�[�V������ID
		MeshAnimatorMaker& motionID(int value);

		// ���[�V�������I�����������[�v�����邩�H
		MeshAnimatorMaker& isLoop(bool value);

		// ���[�V�����̍Đ����x�{��
		MeshAnimatorMaker& motionSpeedRate(float value);

		// ���[�V�����P�R�}�ɉ��b�̎��Ԃ������邩�H
		MeshAnimatorMaker& motionIntervalSec(float value);

		// �ʃt�@�C���ɂȂ��Ă��郂�[�V�����f�[�^���g�p���邩�H
		MeshAnimatorMaker& useOtherMotionData(bool value);

	private:

		// ���g�̃|�C���^
		static MeshAnimatorMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		int m_motionID{ -1 };
		bool m_isLoop{ false };
		float m_motionSpeedRate{ 1.0f };
		float m_motionIntervalSec{ 1.0f / 60.0f };
		bool m_useOtherMotionData{ false };
	};
}
#endif // !MESH_ANIMATOR_MAKER_H_