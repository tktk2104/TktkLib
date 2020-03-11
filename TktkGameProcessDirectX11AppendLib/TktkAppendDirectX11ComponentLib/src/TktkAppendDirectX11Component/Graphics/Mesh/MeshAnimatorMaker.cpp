#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshAnimatorMaker.h"

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

	MeshAnimatorMaker & MeshAnimatorMaker::animationIdImpl(int value)
	{
		m_animationId = value;
		return *this;
	}
}