#include "TktkAppendDxlib3DComponent/Graphics/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3D.h"

#include <algorithm>
#include <Tktk3dCollision/AxisAlignedBoundingBox.h>
#include <Tktk3dCollision/BoundingSphere.h>

#include "TktkAppendDxlib3DComponent/Graphics/Figure/BoxDrawerMaker.h"
#include "TktkAppendDxlib3DComponent/Graphics/Figure/SphereDrawerMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3D::ColliderWireFrameDrawer3D(
		float drawPriority,
		const Color & wireFrameColor
	)
		: m_drawPriority(drawPriority)
		, m_wireFrameColor(wireFrameColor)
	{
	}

	void ColliderWireFrameDrawer3D::start()
	{
		auto boxColliderList = getComponentAll<BoxCollider>();

		std::for_each(
			std::begin(boxColliderList),
			std::end(boxColliderList),
			[this](const auto& node) { createBoxDrawer(node); }
		);

		auto sphereColliderList = getComponentAll<SphereCollider>();

		std::for_each(
			std::begin(sphereColliderList),
			std::end(sphereColliderList),
			[this](const auto& node) { createSphereDrawer(node); }
		);
	}

	void ColliderWireFrameDrawer3D::update()
	{
		m_hasSetActiveClassList.updateContainer();
	}

	void ColliderWireFrameDrawer3D::onEnable()
	{
		m_hasSetActiveClassList.runFunc(true);
	}

	void ColliderWireFrameDrawer3D::onDisable()
	{
		m_hasSetActiveClassList.runFunc(false);
	}

	void ColliderWireFrameDrawer3D::createBoxDrawer(CfpPtr<BoxCollider> boxCollider)
	{
		if (boxCollider.isNull()) return;

		const auto& aabb = dynamic_cast<const AxisAlignedBoundingBox&>(boxCollider->getBodyBase());

		auto boxDrawer = BoxDrawerMaker::makeStart()
			.drawPriority(m_drawPriority)
			.boxColor(m_wireFrameColor)
			.isFill(false)
			.boxSize(aabb.calculateLocalBoxSize())
			.localPosition(aabb.getLocalMatrix().calculateTranslation())
			.useLight(false)
			.create();

		auto cfpPtr = getGameObject()->addComponent(boxDrawer);
		m_hasSetActiveClassList.checkAndAdd<BoxDrawer>(getGameObject()->isStatic(), cfpPtr.processingClassPtr());
	}

	void ColliderWireFrameDrawer3D::createSphereDrawer(CfpPtr<SphereCollider> sphereCollider)
	{
		if (sphereCollider.isNull()) return;

		const auto& boundingSphere = dynamic_cast<const BoundingSphere&>(sphereCollider->getBodyBase());

		auto sphereDrawer = SphereDrawerMaker::makeStart()
			.drawPriority(m_drawPriority)
			.sphereColor(m_wireFrameColor)
			.isFill(false)
			.radius(boundingSphere.calculateLocalRadius())
			.localPosition(boundingSphere.getLocalMatrix().calculateTranslation())
			.useLight(false)
			.create();

		auto cfpPtr = getGameObject()->addComponent(sphereDrawer);
		m_hasSetActiveClassList.checkAndAdd<SphereDrawer>(getGameObject()->isStatic(), cfpPtr.processingClassPtr());
	}
}