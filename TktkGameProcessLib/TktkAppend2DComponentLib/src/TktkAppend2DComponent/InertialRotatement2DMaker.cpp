#include "TktkAppend2DComponent/InertialRotatement2DMaker.h"

namespace tktk
{
	InertialRotatement2DMaker InertialRotatement2DMaker::m_self;

	InertialRotatement2DMaker & InertialRotatement2DMaker::makeStart()
	{
		m_self = InertialRotatement2DMaker();
		return m_self;
	}

	InertialRotatement2D* InertialRotatement2DMaker::create()
	{
		return new InertialRotatement2D(
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
}