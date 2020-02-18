#include "TktkAppend2DComponent/CircleColliderMaker.h"

namespace tktk
{
	CircleColliderMaker CircleColliderMaker::m_self;

	CircleColliderMaker & CircleColliderMaker::makeStart()
	{
		m_self = CircleColliderMaker();
		return m_self;
	}

	CircleCollider* CircleColliderMaker::create()
	{
		return new CircleCollider(
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
}