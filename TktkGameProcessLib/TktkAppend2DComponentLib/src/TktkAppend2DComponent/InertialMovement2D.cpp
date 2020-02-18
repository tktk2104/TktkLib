#include "TktkAppend2DComponent/InertialMovement2D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	InertialMovement2D::InertialMovement2D(
		float decelerationPerSec,
		const Vector2 & initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialMovement2D::update()
	{
		if (m_transform2D.isNull())
		{
			m_transform2D = getComponent<Transform2D>();

			if (m_transform2D.isNull())
			{
				throw std::runtime_error("InertialMovement2D not found Transform2D");
			}
		}

		m_transform2D->addLocalPosition(
			m_velocity * tktk::Time::deltaTime()
		);

		if (!m_preFrameAddForce)
		{
			float speed = (m_velocity.length() - (m_decelerationPerSec * tktk::Time::deltaTime()));

			if (speed < 0.0f) speed = 0.0f;

			m_velocity = Vector2::normalize(m_velocity) * speed;
		}
		m_preFrameAddForce = false;
	}

	void InertialMovement2D::addMomentarilyForce(const Vector2 & force)
	{
		if (force.length() < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		m_velocity += force;
	}

	void InertialMovement2D::addContinuousForce(const Vector2 & force, float accelerationPerSec)
	{
		if (force.length() < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		// –Ú•W‚Æ‚·‚é‘¬“x‚Æ‚Ì·
		Vector2 velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * tktk::Time::deltaTime();

		if (velocityDist.length() > acceleration)
		{
			m_velocity += velocityDist.normalized() * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	const Vector2 & InertialMovement2D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialMovement2D::setVelocity(const Vector2 & velocity)
	{
		m_velocity = velocity;
	}
}