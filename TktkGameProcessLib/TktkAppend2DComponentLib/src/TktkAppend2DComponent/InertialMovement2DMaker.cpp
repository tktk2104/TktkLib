#include "TktkAppend2DComponent/InertialMovement2D.h"
#include "TktkAppend2DComponent/InertialMovement2DMaker.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<InertialMovement2D> InertialMovement2DMaker::create()
	{
		return m_user->createComponent<InertialMovement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);
	}

	InertialMovement2DMaker & InertialMovement2DMaker::decelerationPerSec(float value)
	{
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::initVelocity(const Vector2 & value)
	{
		m_initVelocity = value;
		return *this;
	}

	void InertialMovement2DMaker::reset()
	{
		m_self.m_decelerationPerSec = 64.0f;
		m_self.m_initVelocity = Vector2::zero;
	}
}