#include "TktkAppend3DComponent/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker & SphereColliderMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<SphereCollider>SphereColliderMaker::create()
	{
		return m_user->createComponent<SphereCollider>(
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

	void SphereColliderMaker::reset()
	{
		m_self.m_collisionGroupType = 0;
		m_self.m_radius = 1.0f;
		m_self.m_localPosition = Vector3::zero;
	}
}