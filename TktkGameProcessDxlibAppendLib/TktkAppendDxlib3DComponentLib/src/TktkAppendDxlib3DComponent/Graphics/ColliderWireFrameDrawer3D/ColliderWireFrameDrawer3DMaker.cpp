#include "TktkAppendDxlib3DComponent/Graphics/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker & ColliderWireFrameDrawer3DMaker::makeStart(GameObjectPtr user)
	{
		m_self = ColliderWireFrameDrawer3DMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		return m_user->createComponent<ColliderWireFrameDrawer3D>(
			m_drawPriority,
			m_wireFrameColor
			);
	}

	ColliderWireFrameDrawer3DMaker & ColliderWireFrameDrawer3DMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker & ColliderWireFrameDrawer3DMaker::wireFrameColor(const Color & value)
	{
		m_wireFrameColor = value;
		return *this;
	}
}