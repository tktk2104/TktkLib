#include "TktkAppendDxlib2DComponent/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart()
	{
		m_self = ColliderWireFrameDrawer2DMaker();
		return m_self;
	}

	ColliderWireFrameDrawer2D* ColliderWireFrameDrawer2DMaker::create()
	{
		return new ColliderWireFrameDrawer2D(
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
}