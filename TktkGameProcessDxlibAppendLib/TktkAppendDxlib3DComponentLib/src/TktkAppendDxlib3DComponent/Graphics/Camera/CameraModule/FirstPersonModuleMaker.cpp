#include "TktkAppendDxlib3DComponent/Graphics/Camera/CameraModule/FirstPersonModuleMaker.h"

namespace tktk
{
	FirstPersonModuleMaker FirstPersonModuleMaker::m_self;

	FirstPersonModuleMaker & FirstPersonModuleMaker::makeStart(GameObjectPtr user)
	{
		m_self = FirstPersonModuleMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<FirstPersonModule> FirstPersonModuleMaker::create()
	{
		return m_user->createComponent<FirstPersonModule>(
			m_rotationDegPerPixelOnMouseMove,
			m_moveSpeedPerSec,
			m_alwaysMoveForward,
			m_enableUpDownKey
			);
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::rotationDegPerPixelOnMouseMove(float value)
	{
		m_rotationDegPerPixelOnMouseMove = value;
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
}