#include "TktkAppend2DComponent/InertialMovement2D.h"
#include "TktkAppend2DComponent/InertialMovement2DMaker.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart()
	{
		m_self = InertialMovement2DMaker();
		return m_self;
	}

	InertialMovement2D* InertialMovement2DMaker::create()
	{
		return new InertialMovement2D(
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
}