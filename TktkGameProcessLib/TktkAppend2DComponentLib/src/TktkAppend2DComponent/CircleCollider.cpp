#include "TktkAppend2DComponent/CircleCollider.h"

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkAppend2DComponent/RectCollider.h"
#include "TktkAppend2DComponent/Polygon2dCollider.h"

namespace tktk
{
	CircleCollider::CircleCollider(
		int collisionGroupType,
		float radius,
		const Vector2 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingCircle(radius, localPosition)
	{
	}

	void CircleCollider::update()
	{
		if (m_transform2D.isNull())
		{
			m_transform2D = getComponent<Transform2D>();

			if (m_transform2D.isNull())
			{
				throw std::runtime_error("CircleCollider not found Transform2D");
			}
		}
		m_boundingCircle.transform(m_transform2D->calculateWorldMatrix());
	}

	bool CircleCollider::isCollide(ProcessingClassPtr other)
	{
		if (other->canCast<RectCollider>())
		{
			auto otherCollider = other->castPtr<RectCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<CircleCollider>())
		{
			auto otherCollider = other->castPtr<CircleCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<Polygon2dCollider>())
		{
			auto otherCollider = other->castPtr<Polygon2dCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}
		return false;
	}

	void CircleCollider::onCollide(ProcessingClassPtr other)
	{
		CfpPtr<GameObject> hitObject;

		if (other->canCast<RectCollider>())
		{
			auto otherCollider = other->castPtr<RectCollider>();

			hitObject = otherCollider->getGameObject();
		}

		if (other->canCast<CircleCollider>())
		{
			auto otherCollider = other->castPtr<CircleCollider>();

			hitObject = otherCollider->getGameObject();
		}

		if (other->canCast<Polygon2dCollider>())
		{
			auto otherCollider = other->castPtr<Polygon2dCollider>();

			hitObject = otherCollider->getGameObject();
		}

		m_curHitObjectList.push_front(hitObject);

		auto begin = std::begin(m_preHitObjectList);
		auto end = std::end(m_preHitObjectList);

		auto result = std::find_if(begin, end, [hitObject](CfpPtr<GameObject> node) { return node == hitObject; });

		if (result == end)
		{
			getGameObject()->runOnCollisionEnterAll(hitObject);
			return;
		}
		getGameObject()->runOnCollisionStayAll(hitObject);
	}

	void CircleCollider::afterCollide()
	{
		auto begin = std::begin(m_curHitObjectList);
		auto end = std::end(m_curHitObjectList);

		for (auto gameObject : m_preHitObjectList)
		{
			auto result = std::find_if(begin, end, [gameObject](CfpPtr<GameObject> node) { return node == gameObject; });

			if (result == end)
			{
				getGameObject()->runOnCollisionExitAll(gameObject);
			}
		}
		m_preHitObjectList.swap(m_curHitObjectList);
		m_curHitObjectList.clear();

		m_boundingCircle.transform(m_transform2D->calculateWorldMatrix());
	}

	const Body2dBase & CircleCollider::getBodyBase() const
	{
		return m_boundingCircle;
	}

	const HitInfo2D & CircleCollider::getHitInfo2D() const
	{
		return m_hitInfo;
	}
}