#include "TktkAppendDxlib2DComponent/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2D.h"

#include <Tktk2dCollision/BoundingCircle.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>
#include <TktkAppend2DComponent/CircleCollider.h>
#include <TktkAppend2DComponent/RectCollider.h>
#include <TktkAppend2DComponent/Polygon2dCollider.h>
#include "TktkAppendDxlib2DComponent/Graphics/Figure/CircleDrawerMaker.h"
#include "TktkAppendDxlib2DComponent/Graphics/Figure/Polygon2DDrawerMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2D::ColliderWireFrameDrawer2D(
		float drawPriority,
		const Color & wireFrameColor
	)
		: m_drawPriority(drawPriority)
		, m_wireFrameColor(wireFrameColor)
	{
	}

	void ColliderWireFrameDrawer2D::start()
	{
		auto circleCollider	= getComponent<CircleCollider>();
		if (!circleCollider.expired())
		{
			auto boundingCircle = dynamic_cast<const BoundingCircle&>(circleCollider.lock()->getBodyBase());

			auto circleDrawer = CircleDrawerMaker::makeStart()
				.drawPriority(m_drawPriority)
				.circleColor(m_wireFrameColor)
				.isFill(false)
				.radius(boundingCircle.calculateLocalRadius())
				.create();

			auto processingClassPtr = getGameObject().lock()->addComponent(circleDrawer);
			m_hasSetActiveClassList.checkAndAdd<CircleDrawer>(processingClassPtr);
		}

		auto rectCollider = getComponent<RectCollider>();
		if (!rectCollider.expired())
		{
			auto bundingPolygon = dynamic_cast<const BoundingPolygon2d&>(rectCollider.lock()->getBodyBase());

			auto polygon2DDrawer = Polygon2DDrawerMaker::makeStart()
				.drawPriority(m_drawPriority)
				.polygonColor(m_wireFrameColor)
				.isFill(false)
				.vertexs(bundingPolygon.calculateLocalVertexs())
				.create();

			auto processingClassPtr = getGameObject().lock()->addComponent(polygon2DDrawer);
			m_hasSetActiveClassList.checkAndAdd<Polygon2DDrawer>(processingClassPtr);
		}

		auto polygon2dCollider	= getComponent<Polygon2dCollider>();
		if (!polygon2dCollider.expired())
		{
			auto bundingPolygon = dynamic_cast<const BoundingPolygon2d&>(polygon2dCollider.lock()->getBodyBase());

			auto polygon2DDrawer = Polygon2DDrawerMaker::makeStart()
				.drawPriority(m_drawPriority)
				.polygonColor(m_wireFrameColor)
				.isFill(false)
				.vertexs(bundingPolygon.calculateLocalVertexs())
				.create();

			auto processingClassPtr = getGameObject().lock()->addComponent(polygon2DDrawer);
			m_hasSetActiveClassList.checkAndAdd<Polygon2DDrawer>(processingClassPtr);
		}
	}

	void ColliderWireFrameDrawer2D::update()
	{
		m_hasSetActiveClassList.update();
	}

	void ColliderWireFrameDrawer2D::onEnable()
	{
		m_hasSetActiveClassList.runFunc(true);
	}

	void ColliderWireFrameDrawer2D::onDisable()
	{
		m_hasSetActiveClassList.runFunc(false);
	}
}