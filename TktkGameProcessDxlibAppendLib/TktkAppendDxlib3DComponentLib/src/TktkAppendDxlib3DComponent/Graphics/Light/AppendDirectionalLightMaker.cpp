#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendDirectionalLightMaker.h"

namespace tktk
{
	AppendDirectionalLightMaker AppendDirectionalLightMaker::m_self;

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::makeStart(GameObjectPtr user)
	{
		m_self = AppendDirectionalLightMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<AppendDirectionalLight> AppendDirectionalLightMaker::create()
	{
		return m_user->createComponent<AppendDirectionalLight>(
			m_lightId,
			m_difColor,
			m_spcColor,
			m_ambColor
			);
	}

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::lightId(int value)
	{
		m_lightId = value;
		return *this;
	}

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::difColor(const Color & value)
	{
		m_difColor = value;
		return *this;
	}

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::spcColor(const Color & value)
	{
		m_spcColor = value;
		return *this;
	}

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::ambColor(const Color & value)
	{
		m_ambColor = value;
		return *this;
	}
}