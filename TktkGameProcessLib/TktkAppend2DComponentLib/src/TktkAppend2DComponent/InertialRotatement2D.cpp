#include "TktkAppend2DComponent/InertialRotatement2D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	InertialRotatement2D::InertialRotatement2D(
		float decelerationPerSec,
		float initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialRotatement2D::update()
	{
		if (m_transform2D.isNull())
		{
			m_transform2D = getComponent<Transform2D>();

			if (m_transform2D.isNull())
			{
				throw std::runtime_error("InertialRotatement2D not found Transform2D");
			}
		}

		m_transform2D->addLocalRotationDeg(m_velocity * Time::deltaTime());

		if (!m_preFrameAddForce)
		{
			float speed = std::abs(m_velocity) - (m_decelerationPerSec * Time::deltaTime());

			if (speed < 0.0f) speed = 0.0f;

			m_velocity = MathHelper::sign(m_velocity) * speed;
		}

		m_preFrameAddForce = false;
	}

	void InertialRotatement2D::addMomentarilyForce(float force)
	{
		if (std::abs(force) < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		m_velocity += force;
	}

	void InertialRotatement2D::addContinuousForce(float force, float accelerationPerSec)
	{
		if (std::abs(force) < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		float velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * tktk::Time::deltaTime();

		if (std::abs(velocityDist) > acceleration)
		{
			m_velocity += MathHelper::sign(velocityDist) * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	float InertialRotatement2D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialRotatement2D::setVelocity(float velocity)
	{
		m_velocity = velocity;
	}
}
