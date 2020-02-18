#include "TktkAppend3DComponent/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker & BoxColliderMaker::makeStart()
	{
		m_self = BoxColliderMaker();
		return m_self;
	}

	BoxCollider* BoxColliderMaker::create()
	{
		return new BoxCollider(
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
}