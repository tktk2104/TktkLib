#include "TktkAppend2DComponent/CircleColliderMaker.h"

namespace tktk
{
	CircleColliderMaker CircleColliderMaker::m_self;

	CircleColliderMaker & CircleColliderMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<CircleCollider> CircleColliderMaker::create()
	{
		return m_user->createComponent<CircleCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition
			);
	}

	CircleColliderMaker & CircleColliderMaker::collisionGroupType(int value)
	{
		m_collisionGroupType = value;
		return *this;
	}

	CircleColliderMaker & CircleColliderMaker::radius(float value)
	{
		m_radius = value;
		return *this;
	}

	CircleColliderMaker & CircleColliderMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}

	void CircleColliderMaker::reset()
	{
		m_self.m_collisionGroupType = 0;
		m_self.m_radius = 1.0f;
		m_self.m_localPosition = Vector2::zero;
	}
}