#include "TktkAppendDxlib3DComponent/Graphics/Light/AppendDirectionalLightMaker.h"

namespace tktk
{
	AppendDirectionalLightMaker AppendDirectionalLightMaker::m_self;

	AppendDirectionalLightMaker & AppendDirectionalLightMaker::makeStart()
	{
		m_self = AppendDirectionalLightMaker();
		return m_self;
	}

	std::shared_ptr<AppendDirectionalLight> AppendDirectionalLightMaker::create()
	{
		return std::make_shared<AppendDirectionalLight>(
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