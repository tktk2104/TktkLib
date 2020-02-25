#include "TktkAppendDirectX11Component/Graphics/Light/PointLightMaker.h"

namespace tktk
{
	PointLightMaker PointLightMaker::m_self;

	PointLightMaker & PointLightMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<PointLight> PointLightMaker::create()
	{
		return m_user->createComponent<PointLight>(
			m_lightId,
			m_ambientColor,
			m_diffuseColor,
			m_specularColor
			);
	}

	PointLightMaker & PointLightMaker::lightId(int value)
	{
		m_lightId = value;
		return *this;
	}

	PointLightMaker & PointLightMaker::ambientColor(const Color & value)
	{
		m_ambientColor = value;
		return *this;
	}

	PointLightMaker & PointLightMaker::diffuseColor(const Color & value)
	{
		m_diffuseColor = value;
		return *this;
	}

	PointLightMaker & PointLightMaker::specularColor(const Color & value)
	{
		m_specularColor = value;
		return *this;
	}

	void PointLightMaker::reset()
	{
		m_self.m_lightId = 0;
		m_self.m_ambientColor = Color(0.3f, 0.3f, 0.3f, 1.0f);
		m_self.m_diffuseColor = Color::white;
		m_self.m_specularColor = Color::white;
	}
}