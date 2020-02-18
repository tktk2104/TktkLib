#include "TktkAppendDxlib3DComponent/Graphics/Light/BasicDirectionalLightMaker.h"

namespace tktk
{
	BasicDirectionalLightMaker BasicDirectionalLightMaker::m_self;

	BasicDirectionalLightMaker & BasicDirectionalLightMaker::makeStart()
	{
		m_self = BasicDirectionalLightMaker();
		return m_self;
	}

	std::shared_ptr<BasicDirectionalLight> BasicDirectionalLightMaker::create()
	{
		return std::make_shared<BasicDirectionalLight>(
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