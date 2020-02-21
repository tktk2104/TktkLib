#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDrawerMaker.h"

namespace tktk
{
	ShadowMapDrawerMaker ShadowMapDrawerMaker::m_self;

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::makeStart()
	{
		m_self = ShadowMapDrawerMaker();
		return m_self;
	}

	ShadowMapDrawer* ShadowMapDrawerMaker::create()
	{
		return new ShadowMapDrawer(
			m_shadowMapCreateStarterDrawPriority,
			m_shadowMapCreateFinisherDrawPriority,
			m_shadowMapEnablerDrawPriority,
			m_shadowMapDisablerDrawPriority,
			m_shadowMapId,
			m_drawAreaMinPos,
			m_drawAreaMaxPos
			);
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::shadowMapCreateStarterDrawPriority(float value)
	{
		m_shadowMapCreateStarterDrawPriority = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::shadowMapCreateFinisherDrawPriority(float value)
	{
		m_shadowMapCreateFinisherDrawPriority = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::shadowMapEnablerDrawPriority(float value)
	{
		m_shadowMapEnablerDrawPriority = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::shadowMapDisablerDrawPriority(float value)
	{
		m_shadowMapDisablerDrawPriority = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::shadowMapId(int value)
	{
		m_shadowMapId = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::drawAreaMinPos(const Vector3 & value)
	{
		m_drawAreaMinPos = value;
		return *this;
	}

	ShadowMapDrawerMaker & ShadowMapDrawerMaker::drawAreaMaxPos(const Vector3 & value)
	{
		m_drawAreaMaxPos = value;
		return *this;
	}
}