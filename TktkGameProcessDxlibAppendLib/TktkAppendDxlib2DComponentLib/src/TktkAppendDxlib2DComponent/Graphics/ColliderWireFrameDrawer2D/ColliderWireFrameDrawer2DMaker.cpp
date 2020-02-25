#include "TktkAppendDxlib2DComponent/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		return m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_wireFrameColor
			);
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::wireFrameColor(const Color & value)
	{
		m_wireFrameColor = value;
		return *this;
	}

	void ColliderWireFrameDrawer2DMaker::reset()
	{
		m_self.m_drawPriority = 0.0f;
		m_self.m_wireFrameColor = Color::white;
	}
}