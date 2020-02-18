#include "TktkAppendDxlib3DComponent/Graphics/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker & ColliderWireFrameDrawer3DMaker::makeStart()
	{
		m_self = ColliderWireFrameDrawer3DMaker();
		return m_self;
	}

	std::shared_ptr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		return std::make_shared<ColliderWireFrameDrawer3D>(
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