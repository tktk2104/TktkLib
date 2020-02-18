#include "TktkAppend3DComponent/BoxCollider.h"

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkAppend3DComponent/SphereCollider.h"

namespace tktk
{
	BoxCollider::BoxCollider(
		int collisionGroupType,
		const Vector3 & boxSize,
		const Vector3 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingBox(boxSize, localPosition)
	{
	}

	void BoxCollider::update()
	{
		if (m_transform3D.isNull())
		{
			m_transform3D = getComponent<Transform3D>();

			if (m_transform3D.isNull())
			{
				throw std::runtime_error("RectCollider not found Transform3D");
			}
		}
		m_boundingBox.transform(m_transform3D->calculateWorldMatrix());
	}

	bool BoxCollider::isCollide(ProcessingClassPtr other)
	{
		if (other->canCast<BoxCollider>())
		{
			auto otherCollider = other->castPtr<BoxCollider>();

			return m_boundingBox.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<SphereCollider>())
		{
			auto otherCollider = other->castPtr<SphereCollider>();

			return m_boundingBox.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		return false;
	}

	void BoxCollider::onCollide(ProcessingClassPtr other)
	{
		CfpPtr<GameObject> hitObject;

		if (other->canCast<BoxCollider>())
		{
			auto otherCollider = other->castPtr<BoxCollider>();

			hitObject = otherCollider->getGameObject();
		}

		if (other->canCast<SphereCollider>())
		{
			auto otherCollider = other->castPtr<SphereCollider>();

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

	void BoxCollider::afterCollide()
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

		m_boundingBox.transform(m_transform3D->calculateWorldMatrix());
	}

	const Body3dBase & BoxCollider::getBodyBase() const
	{
		return m_boundingBox;
	}

	const HitInfo3D & BoxCollider::getHitInfo3D() const
	{
		return m_hitInfo;
	}
}