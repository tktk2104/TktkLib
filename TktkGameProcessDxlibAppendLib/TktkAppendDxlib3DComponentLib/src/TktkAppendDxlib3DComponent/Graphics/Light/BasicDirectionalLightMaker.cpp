#include "TktkAppendDxlib3DComponent/Graphics/Light/BasicDirectionalLightMaker.h"

namespace tktk
{
	BasicDirectionalLightMaker BasicDirectionalLightMaker::m_self;

	BasicDirectionalLightMaker & BasicDirectionalLightMaker::makeStart(GameObjectPtr user)
	{
		m_self = BasicDirectionalLightMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<BasicDirectionalLight> BasicDirectionalLightMaker::create()
	{
		return m_user->createComponent<BasicDirectionalLight>(
			m_difColor,
			m_spcColor,
			m_ambColor
			);
	}

	BasicDirectionalLightMaker & BasicDirectionalLightMaker::difColor(const Color & value)
	{
		m_difColor = value;
		return *this;
	}

	BasicDirectionalLightMaker & BasicDirectionalLightMaker::spcColor(const Color & value)
	{
		m_spcColor = value;
		return *this;
	}

	BasicDirectionalLightMaker & BasicDirectionalLightMaker::ambColor(const Color & value)
	{
		m_ambColor = value;
		return *this;
	}
}