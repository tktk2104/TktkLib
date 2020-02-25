#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshAnimatorMaker.h"

namespace tktk
{
	MeshAnimatorMaker MeshAnimatorMaker::m_self;

	MeshAnimatorMaker & MeshAnimatorMaker::makeStart(GameObjectPtr user)
	{
		m_self = MeshAnimatorMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<MeshAnimator> MeshAnimatorMaker::create()
	{
		return m_user->createComponent<MeshAnimator>(
			m_motionID,
			m_isLoop,
			m_motionSpeedRate,
			m_motionIntervalSec,
			m_useOtherMotionData
			);
	}

	MeshAnimatorMaker & MeshAnimatorMaker::motionID(int value)
	{
		m_motionID = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::motionSpeedRate(float value)
	{
		m_motionSpeedRate = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::motionIntervalSec(float value)
	{
		m_motionIntervalSec = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::useOtherMotionData(bool value)
	{
		m_useOtherMotionData = value;
		return *this;
	}
}