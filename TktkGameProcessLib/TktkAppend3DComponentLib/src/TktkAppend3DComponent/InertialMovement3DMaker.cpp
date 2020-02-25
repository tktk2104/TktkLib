#include "TktkAppend3DComponent/InertialMovement3DMaker.h"

namespace tktk
{
	InertialMovement3DMaker InertialMovement3DMaker::m_self;

	InertialMovement3DMaker & InertialMovement3DMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<InertialMovement3D> InertialMovement3DMaker::craete()
	{
		return m_user->createComponent<InertialMovement3D>(
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

	void InertialMovement3DMaker::reset()
	{
		m_self.m_decelerationPerSec = 64.0f;
		m_self.m_initVelocity = Vector3::zero;
	}
}