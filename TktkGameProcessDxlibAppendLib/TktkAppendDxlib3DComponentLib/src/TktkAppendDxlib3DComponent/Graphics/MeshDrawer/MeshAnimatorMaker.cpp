#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshAnimatorMaker.h"

namespace tktk
{
	MeshAnimatorMaker MeshAnimatorMaker::m_self;

	MeshAnimatorMaker & MeshAnimatorMaker::makeStart()
	{
		m_self = MeshAnimatorMaker();
		return m_self;
	}

	MeshAnimator* MeshAnimatorMaker::create()
	{
		return new MeshAnimator(
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