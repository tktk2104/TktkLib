#include "TktkAppend3DComponent/InertialMovement3DMaker.h"

namespace tktk
{
	InertialMovement3DMaker InertialMovement3DMaker::m_self;

	InertialMovement3DMaker & InertialMovement3DMaker::makeStart()
	{
		m_self = InertialMovement3DMaker();
		return m_self;
	}

	InertialMovement3D* InertialMovement3DMaker::craete()
	{
		return new InertialMovement3D(
			m_decelerationPerSec,
			m_initVelocity
		);
	}

	InertialMovement3DMaker & InertialMovement3DMaker::decelerationPerSec(float value)
	{
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement3DMaker & InertialMovement3DMaker::initVelocity(const Vector3 & value)
	{
		m_initVelocity = value;
		return *this;
	}
}