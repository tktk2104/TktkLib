#include "TktkAppend2DComponent/Polygon2dColliderMaker.h"

namespace tktk
{
	Polygon2dColliderMaker Polygon2dColliderMaker::m_self;

	Polygon2dColliderMaker & Polygon2dColliderMaker::makeStart()
	{
		m_self = Polygon2dColliderMaker();
		return m_self;
	}

	Polygon2dCollider* Polygon2dColliderMaker::create()
	{
		return new Polygon2dCollider(
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
}