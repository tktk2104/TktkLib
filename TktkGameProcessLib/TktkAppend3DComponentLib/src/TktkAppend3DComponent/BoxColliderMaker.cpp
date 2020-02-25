#include "TktkAppend3DComponent/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker & BoxColliderMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<BoxCollider> BoxColliderMaker::create()
	{
		return m_user->createComponent<BoxCollider>(
			m_collisionGroupType,
			m_boxSize,
			m_localPosition
			);
	}

	BoxColliderMaker & BoxColliderMaker::collisionGroupType(int value)
	{
		m_collisionGroupType = value;
		return *this;
	}

	BoxColliderMaker & BoxColliderMaker::boxSize(const Vector3 & value)
	{
		m_boxSize = value;
		return *this;
	}

	BoxColliderMaker & BoxColliderMaker::localPosition(const Vector3 & value)
	{
		m_localPosition = value;
		return *this;
	}

	void BoxColliderMaker::reset()
	{
		m_self.m_collisionGroupType = 0;
		m_self.m_boxSize = Vector3::one;
		m_self.m_localPosition = Vector3::zero;
	}
}