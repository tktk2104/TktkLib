#include "TktkAppend2DComponent/RectColliderMaker.h"

namespace tktk
{
	RectColliderMaker RectColliderMaker::m_self;

	RectColliderMaker & RectColliderMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<RectCollider> RectColliderMaker::create()
	{
		return m_user->createComponent<RectCollider>(
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

	void RectColliderMaker::reset()
	{
		m_self.m_collisionGroupType = 0;
		m_self.m_rectSize = Vector2::one;
		m_self.m_localPosition = Vector2::zero;
	}
}