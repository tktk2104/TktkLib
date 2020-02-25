#include "TktkAppend2DComponent/InertialRotatement2DMaker.h"

namespace tktk
{
	InertialRotatement2DMaker InertialRotatement2DMaker::m_self;

	InertialRotatement2DMaker & InertialRotatement2DMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<InertialRotatement2D> InertialRotatement2DMaker::create()
	{
		return m_user->createComponent<InertialRotatement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::decelerationPerSec(float value)
	{
		m_decelerationPerSec = value;
		return *this;
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::initVelocity(float value)
	{
		m_initVelocity = value;
		return *this;
	}

	void InertialRotatement2DMaker::reset()
	{
		m_self.m_decelerationPerSec = 30.0f;
		m_self.m_initVelocity = 0.0f;
	}
}