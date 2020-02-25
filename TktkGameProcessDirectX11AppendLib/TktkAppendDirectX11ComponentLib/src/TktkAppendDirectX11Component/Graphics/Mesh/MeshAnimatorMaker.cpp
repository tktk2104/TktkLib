#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimatorMaker.h"

namespace tktk
{
	MeshAnimatorMaker MeshAnimatorMaker::m_self;

	MeshAnimatorMaker & MeshAnimatorMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<MeshAnimator> MeshAnimatorMaker::create()
	{
		return m_user->createComponent<MeshAnimator>(
			m_meshDrawer,
			m_animationId,
			m_animFrameIntervalPerSec,
			m_animSpeedRate
			);
	}

	MeshAnimatorMaker & MeshAnimatorMaker::meshDrawer(CfpPtr<MeshDrawer> value)
	{
		m_meshDrawer = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::animationId(int value)
	{
		m_animationId = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::animFrameIntervalPerSec(float value)
	{
		m_animFrameIntervalPerSec = value;
		return *this;
	}

	MeshAnimatorMaker & MeshAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}

	void MeshAnimatorMaker::reset()
	{
		m_self.m_meshDrawer = CfpPtr<MeshDrawer>();
		m_self.m_animationId = 0;
		m_self.m_animFrameIntervalPerSec = 60.0f;
		m_self.m_animSpeedRate = 1.0f;
	}
}