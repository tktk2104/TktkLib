#include "TktkAppend2DComponent/RectColliderExtrusionMaker.h"

namespace tktk
{
	RectColliderExtrusionMaker RectColliderExtrusionMaker::m_self;

	RectColliderExtrusionMaker & RectColliderExtrusionMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<RectColliderExtrusion> RectColliderExtrusionMaker::create()
	{
		return m_user->createComponent<RectColliderExtrusion>();
	}

	void RectColliderExtrusionMaker::reset()
	{
	}
}