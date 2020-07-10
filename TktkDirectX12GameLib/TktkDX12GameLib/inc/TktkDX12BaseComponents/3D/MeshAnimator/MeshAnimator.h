#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// ���b�V�����A�j���[�V����������R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FBasicMeshDrawer�z
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(unsigned int initMotionId);

	public:

		void update();

		// �����̃X�P���g�������g�̃��[�V�����ŕό`������
		void transformSkeleton(unsigned int skeletonId);

	public:

		// ���[�V������V���ɐݒ肷��
		void setMotionId(unsigned int motionId);

	private:

		unsigned int m_motionId;
		unsigned int m_curFrame{ 0U };
	};
}
#endif // !MESH_ANIMATOR_H_