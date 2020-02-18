#include "TktkAppend3DComponent/InertialMovement3D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkComponentFramework/Time/Time.h>

namespace tktk
{
	InertialMovement3D::InertialMovement3D(
		float decelerationPerSec,
		const Vector3 & initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialMovement3D::update()
	{
		if (m_transform3D.isNull())
		{
			m_transform3D = getComponent<Transform3D>();

			if (m_transform3D.isNull())
			{
				throw std::runtime_error("InertialMovement3D not found Transform3D");
			}
		}

		m_transform3D->addLocalPosition(m_velocity * Time::deltaTime());

		if (!m_preFrameAddForce)
		{
			float speed = (m_velocity.length() - (m_decelerationPerSec * Time::deltaTime()));

			if (speed < 0.0f) speed = 0.0f;

			m_velocity = Vector3::normalize(m_velocity) * speed;
		}
		m_preFrameAddForce = false;
	}

	void InertialMovement3D::addMomentarilyForce(const Vector3 & force)
	{
		if (force.length() < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		m_velocity += force;
	}

	void InertialMovement3D::addContinuousForce(const Vector3 & force, float accelerationPerSec)
	{
		if (force.length() < MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		// –Ú•W‚Æ‚·‚é‘¬“x‚Æ‚Ì·
		Vector3 velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * tktk::Time::deltaTime();

		if (velocityDist.length() > acceleration)
		{
			m_velocity += velocityDist.normalized() * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	Vector3 InertialMovement3D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialMovement3D::setVelocity(const Vector3 & velocity)
	{
		m_velocity = velocity;
	}
}