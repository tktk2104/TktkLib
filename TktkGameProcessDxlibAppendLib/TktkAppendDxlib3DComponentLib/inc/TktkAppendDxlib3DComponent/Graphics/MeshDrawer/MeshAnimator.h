#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "MeshDrawer.h"

namespace tktk
{
	// �uMeshDrawer�v�ŕ`�悵�����b�V�����A�j���[�V����������R���|�[�l���g
	// �y�O��R���|�[�l���g�FMeshDrawer�z
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(
			int motionID,				// �Đ����郂�[�V������ID
			bool isLoop,				// ���[�V�������I�����������[�v�����邩�H
			float motionSpeedRate,		// ���[�V�����̍Đ����x�{��
			float motionIntervalSec,	// ���[�V�����P�R�}�ɉ��b�̎��Ԃ������邩�H
			bool useOtherMotionData		// �ʃt�@�C���ɂȂ��Ă��郂�[�V�����f�[�^���g�p���邩�H
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// ���[�V������ύX
		void changeMotion(
			int motionID,			// �Đ����郂�[�V������ID
			bool isLoop,			// ���[�V�������I�����������[�v�����邩�H
			float lerpTimeSec,		// ���[�V�����J�ڂ̕⊮�����b�����邩�H
			bool useOtherMotionData	// �ʃt�@�C���ɂȂ��Ă��郂�[�V�����f�[�^���g�p���邩�H
		);

		// �Đ����Ă��郂�[�V�����ԍ����擾
		int getCurMotionID() const;

		// ���[�V�������I�����������擾
		bool isEndAnimation() const;

		// �Đ����Ă��郂�[�V���������b�Ԃ̒������������擾
		float getCurMotionEndTime() const;

		// ���[�V�����̍Đ����x�{�����擾
		float getMotionSpeedRate() const;

		// ���[�V�����̍Đ����x�{�����Đݒ�
		void setMotionSpeedRate(float speed);

	private:

		CfpPtr<MeshDrawer> m_meshDrawer;

		// �ʃt�@�C���ɂȂ��Ă��郂�[�V���������ݎg�p���Ă��邩
		bool m_curUseOtherMotionData;

		// �ʃt�@�C���ɂȂ��Ă��郂�[�V�������P�O�Ɏg�p���Ă�����
		bool m_preUseOtherMotionData;

		// ���݂̃��[�V������ID
		int m_curMotionID;

		// �P�O�̃��[�V������ID
		int m_preMotionID;

		// ���[�V���������[�v�����邩
		bool m_isLoop;

		// ���[�V�����̃X�s�[�h�i�{���j
		float m_motionSpeedRate;

		// �A�j���[�V�����P�R�}�ɂ����鎞�ԁi�b�j
		float m_motionIntervalSec;

		// ���݂̃��[�V�����̃^�C�}�[
		float m_curMotionTimer{ 0.0f };

		// 1�O�̃��[�V�����̃^�C�}�[
		float m_preMotionTimer{ 0.0f };

		// ���[�V�����⊮�^�C�}�[
		float m_lerpSecTimer{ 0.0f };

		// ���[�V�����⊮����
		float m_lerpTimeSec{ 0.1f };
	};
}
#endif // !MESH_ANIMATOR_H_