#include "TktkAppendDirectX11Component/Graphics/Camera/Module/FirstPersonModuleMaker.h"

namespace tktk
{
	FirstPersonModuleMaker FirstPersonModuleMaker::m_self;

	FirstPersonModuleMaker & FirstPersonModuleMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<FirstPersonModule> FirstPersonModuleMaker::create()
	{
		return m_user->createComponent<FirstPersonModule>(
			m_rotateDegSpeedPerSec,
			m_moveSpeedPerSec,
			m_alwaysMoveForward,
			m_enableUpDownKey
			);
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::rotateDegSpeedPerSec(float value)
	{
		m_rotateDegSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::moveSpeedPerSec(float value)
	{
		m_moveSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::alwaysMoveForward(bool value)
	{
		m_alwaysMoveForward = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::enableUpDownKey(bool value)
	{
		m_enableUpDownKey = value;
		return *this;
	}

	void FirstPersonModuleMaker::reset()
	{
		m_self.m_rotateDegSpeedPerSec = 100.0f;
		m_self.m_moveSpeedPerSec = 100.0f;
		m_self.m_alwaysMoveForward = false;
		m_self.m_enableUpDownKey = false;
	}
}