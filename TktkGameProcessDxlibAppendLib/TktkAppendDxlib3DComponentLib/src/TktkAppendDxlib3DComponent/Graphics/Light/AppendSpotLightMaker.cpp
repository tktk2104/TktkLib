#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendSpotLightMaker.h"

namespace tktk
{
	AppendSpotLightMaker AppendSpotLightMaker::m_self;

	AppendSpotLightMaker & AppendSpotLightMaker::makeStart(GameObjectPtr user)
	{
		m_self = AppendSpotLightMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<AppendSpotLight> AppendSpotLightMaker::create()
	{
		return m_user->createComponent<AppendSpotLight>(
			m_lightId,
			m_outAngleDegree,
			m_inAngleDegree,
			m_range,
			m_attenuation,
			m_difColor,
			m_spcColor,
			m_ambColor
			);
	}

	AppendSpotLightMaker & AppendSpotLightMaker::lightId(int value)
	{
		m_lightId = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::outAngleDegree(float value)
	{
		m_outAngleDegree = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::inAngleDegree(float value)
	{
		m_inAngleDegree = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::range(float value)
	{
		m_range = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::attenuation(const std::array<float, 3>& value)
	{
		m_attenuation = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::difColor(const Color & value)
	{
		m_difColor = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::spcColor(const Color & value)
	{
		m_spcColor = value;
		return *this;
	}

	AppendSpotLightMaker & AppendSpotLightMaker::ambColor(const Color & value)
	{
		m_ambColor = value;
		return *this;
	}
}