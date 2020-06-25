#include "TktkDX12Game/Component/DefaultComponents/3DComponents/MeshAnimator/MeshAnimator.h"

namespace tktk
{
	MeshAnimator::MeshAnimator(unsigned int motionId)
		: m_motionId(motionId)
	{
	}

	void MeshAnimator::update()
	{
		m_curFrame++;
	}

	void MeshAnimator::transformSkeleton(unsigned int skeletonId)
	{
		if (isActive())
		{
			DX12GameManager::updateMotion(skeletonId, m_motionId, m_curFrame);
		}
	}

	void MeshAnimator::setMotionId(unsigned int motionId)
	{
		m_motionId = motionId;
	}
}