#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendPointLightMaker.h"

namespace tktk
{
	AppendPointLightMaker AppendPointLightMaker::m_self;

	AppendPointLightMaker & AppendPointLightMaker::makeStart()
	{
		m_self = AppendPointLightMaker();
		return m_self;
	}

	AppendPointLight* AppendPointLightMaker::create()
	{
		return new AppendPointLight(
			m_lightId,
			m_range,
			m_attenuation,
			m_difColor,
			m_spcColor,
			m_ambColor
			);
	}

	AppendPointLightMaker & AppendPointLightMaker::lightId(int value)
	{
		m_lightId = value;
		return *this;
	}

	AppendPointLightMaker & AppendPointLightMaker::range(float value)
	{
		m_range = value;
		return *this;
	}

	AppendPointLightMaker & AppendPointLightMaker::attenuation(const std::array<float, 3>& value)
	{
		m_attenuation = value;
		return *this;
	}

	AppendPointLightMaker & AppendPointLightMaker::difColor(const Color & value)
	{
		m_difColor = value;
		return *this;
	}

	AppendPointLightMaker & AppendPointLightMaker::spcColor(const Color & value)
	{
		m_spcColor = value;
		return *this;
	}

	AppendPointLightMaker & AppendPointLightMaker::ambColor(const Color & value)
	{
		m_ambColor = value;
		return *this;
	}
}