#include "TktkAppendDirectX11Component/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart(GameObjectPtr user)
	{
		m_self = ColliderWireFrameDrawer2DMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		return m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_lineColor
			);
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::lineColor(const Color & value)
	{
		m_lineColor = value;
		return *this;
	}
}