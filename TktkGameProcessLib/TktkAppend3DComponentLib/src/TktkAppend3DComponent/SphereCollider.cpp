#include "TktkAppend3DComponent/SphereCollider.h"

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkAppend3DComponent/BoxCollider.h"

namespace tktk
{
	SphereCollider::SphereCollider(
		int collisionGroupType,
		float radius,
		const Vector3 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingSphere(radius, localPosition)
	{
	}

	void SphereCollider::update()
	{
		if (m_transform3D.isNull())
		{
			auto m_transform3D = getComponent<Transform3D>();

			if (m_transform3D.isNull())
			{
				throw std::runtime_error("RectCollider not found Transform3D");
			}
		}
		m_boundingSphere.transform(m_transform3D->calculateWorldMatrix());
	}

	bool SphereCollider::isCollide(ProcessingClassPtr other)
	{
		if (other->canCast<BoxCollider>())
		{
			auto otherCollider = other->castPtr<BoxCollider>();

			return m_boundingSphere.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other->canCast<SphereCollider>())
		{
			auto otherCollider = other->castPtr<SphereCollider>();

			return m_boundingSphere.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		return false;
	}

	void SphereCollider::onCollide(ProcessingClassPtr other)
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

	void SphereCollider::afterCollide()
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

		m_boundingSphere.transform(m_transform3D->calculateWorldMatrix());
	}

	const Body3dBase & SphereCollider::getBodyBase() const
	{
		return m_boundingSphere;
	}

	const HitInfo3D & SphereCollider::getHitInfo3D() const
	{
		return m_hitInfo;
	}
}