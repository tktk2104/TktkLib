#include "TktkAppend2DComponent/RectColliderExtrusionMaker.h"

namespace tktk
{
	RectColliderExtrusionMaker RectColliderExtrusionMaker::m_self;

	RectColliderExtrusionMaker & RectColliderExtrusionMaker::makeStart()
	{
		m_self = RectColliderExtrusionMaker();
		return m_self;
	}

	RectColliderExtrusion* RectColliderExtrusionMaker::create()
	{
		return new RectColliderExtrusion();
	}
}