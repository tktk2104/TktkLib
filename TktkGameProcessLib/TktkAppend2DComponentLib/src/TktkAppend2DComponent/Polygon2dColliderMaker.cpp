#include "TktkAppend2DComponent/Polygon2dColliderMaker.h"

namespace tktk
{
	Polygon2dColliderMaker Polygon2dColliderMaker::m_self;

	Polygon2dColliderMaker & Polygon2dColliderMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<Polygon2dCollider> Polygon2dColliderMaker::create()
	{
		return m_user->createComponent<Polygon2dCollider>(
			m_collisionGroupType,
			m_vertexs,
			m_localPosition
			);
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::collisionGroupType(int value)
	{
		m_collisionGroupType = value;
		return *this;
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::vertexs(const std::vector<Vector2> & value)
	{
		m_vertexs = value;
		return *this;
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}

	void Polygon2dColliderMaker::reset()
	{
		m_self.m_collisionGroupType = 0;
		m_self.m_vertexs = {};
		m_self.m_localPosition = { Vector2::zero };
	}
}