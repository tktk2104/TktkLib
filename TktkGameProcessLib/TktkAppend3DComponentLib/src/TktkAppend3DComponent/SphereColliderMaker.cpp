#include "TktkAppend3DComponent/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker & SphereColliderMaker::makeStart()
	{
		m_self = SphereColliderMaker();
		return m_self;
	}

	SphereCollider* SphereColliderMaker::create()
	{
		return new SphereCollider(
			m_collisionGroupType,
			m_radius,
			m_localPosition
		);
	}

	SphereColliderMaker & SphereColliderMaker::collisionGroupType(int value)
	{
		m_collisionGroupType = value;
		return *this;
	}

	SphereColliderMaker & SphereColliderMaker::radius(float value)
	{
		m_radius = value;
		return *this;
	}

	SphereColliderMaker & SphereColliderMaker::localPosition(const Vector3 & value)
	{
		m_localPosition = value;
		return *this;
	}
}