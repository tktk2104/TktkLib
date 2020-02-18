#include "TktkAppend2DComponent/RectCollider.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkAppend2DComponent/CircleCollider.h"
#include "TktkAppend2DComponent/Polygon2dCollider.h"

namespace tktk
{
	RectCollider::RectCollider(
		int collisionGroupType,
		const Vector2& rectSize,
		const Vector2& localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingPolygon2d(
			std::vector<Vector2>(
				{
					Vector2(-rectSize.x / 2, -rectSize.y / 2),
					Vector2(rectSize.x / 2, -rectSize.y / 2),
					Vector2(rectSize.x / 2,  rectSize.y / 2),
					Vector2(-rectSize.x / 2,  rectSize.y / 2)
				})
			, localPosition
		)
	{
	}

	void RectCollider::update()
	{
		if (m_transform2D.isNull())
		{
			m_transform2D = getComponent<Transform2D>();

			if (m_transform2D.isNull())
			{
				throw std::runtime_error("RectCollider not found Transform2D");
			}
		}

		m_boundingPolygon2d.transform(m_transform2D->calculateWorldMatrix());
	}

	bool RectCollider::isCollide(ProcessingClassPtr other)
	{
		if (other->canCast<RectCollider>())
		{
			auto otherCollider = other->castPtr<RectCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<CircleCollider>())
		{
			auto otherCollider = other->castPtr<CircleCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<Polygon2dCollider>())
		{
			auto otherCollider = other->castPtr<Polygon2dCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}
		return false;
	}

	void RectCollider::onCollide(ProcessingClassPtr other)
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

	void RectCollider::afterCollide()
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

		m_boundingPolygon2d.transform(m_transform2D->calculateWorldMatrix());
	}

	const Body2dBase & RectCollider::getBodyBase() const
	{
		return m_boundingPolygon2d;
	}
}