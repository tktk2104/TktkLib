#include "TktkAppend2DComponent/RectColliderMaker.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart()
	{
		m_self = RectColliderMaker();
		return m_self;
	}

	RectCollider* RectColliderMaker::create()
	{
		return new RectCollider(
			m_collisionGroupType,
			m_rectSize,
			m_localPosition
		);
	}

	RectColliderMaker & RectColliderMaker::collisionGroupType(int value)
	{
		m_collisionGroupType = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::rectSize(const Vector2 & value)
	{
		m_rectSize = value;
		return *this;
	}

	RectColliderMaker & RectColliderMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}
}