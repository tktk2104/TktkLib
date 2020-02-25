#include "TktkAppendDirectX11Component/Graphics/Camera/SimpleCameraMaker.h"

namespace tktk
{
	SimpleCameraMaker SimpleCameraMaker::m_self;

	SimpleCameraMaker & SimpleCameraMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SimpleCamera> SimpleCameraMaker::create()
	{
		return m_user->createComponent<SimpleCamera>(
			m_cameraId,
			m_cameraFov,
			m_cameraNear,
			m_cameraFar
			);
	}

	SimpleCameraMaker & SimpleCameraMaker::cameraId(int value)
	{
		m_cameraId = value;
		return *this;
	}

	SimpleCameraMaker & SimpleCameraMaker::cameraFov(float value)
	{
		m_cameraFov = value;
		return *this;
	}

	SimpleCameraMaker & SimpleCameraMaker::cameraNear(float value)
	{
		m_cameraNear = value;
		return *this;
	}

	SimpleCameraMaker & SimpleCameraMaker::cameraFar(float value)
	{
		m_cameraFar = value;
		return *this;
	}

	void SimpleCameraMaker::reset()
	{
		m_self.m_cameraId = 0;
		m_self.m_cameraFov = 45.0f;
		m_self.m_cameraNear = 0.01f;
		m_self.m_cameraFar = 1000.0f;
	}
}