#include "TktkAppendDirectX11Component/Graphics/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2D.h"

#include <algorithm>
#include <TktkMath/MathHelper.h>
#include <TktkAppend2DComponent/CircleCollider.h>
#include <TktkAppend2DComponent/RectCollider.h>
#include <TktkAppend2DComponent/Polygon2dCollider.h>
#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/SystemBlendStateId.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/SystemDepthStencilStateId.h"

namespace tktk
{
	ColliderWireFrameDrawer2D::ColliderWireFrameDrawer2D(float drawPriority, const Color & lineColor)
		: m_drawPriority(drawPriority)
		, m_lineColor(lineColor)
	{
	}

	void ColliderWireFrameDrawer2D::start()
	{
		auto circleColliderList = getComponentAll<CircleCollider>();

		for (const auto & circleCollider : circleColliderList)
		{
			const BoundingCircle& boundingCircle = static_cast<const BoundingCircle&>(circleCollider->getBodyBase());

			std::vector<Vector2> vertexArray;
			vertexArray.reserve(20U + 1U);

			float baseAngle = 360.0f / 20U;

			for (unsigned int i = 0; i < 20U; i++)
			{
				vertexArray.push_back(
					Vector2(MathHelper::cos(baseAngle * i) * boundingCircle.calculateLocalRadius(), MathHelper::sin(baseAngle * i) * boundingCircle.calculateLocalRadius()) + boundingCircle.getLocalMatrix().calculateTranslation()
				);
			}

			vertexArray.push_back(Vector2(MathHelper::cos(0) * boundingCircle.calculateLocalRadius(), MathHelper::sin(0) * boundingCircle.calculateLocalRadius()) + boundingCircle.getLocalMatrix().calculateTranslation());
			
			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					static_cast<int>(SystemBlendStateId::Alpha),
					static_cast<int>(SystemDepthStencilStateId::NotUseDepth),
					Color::white
					)
			);
		}

		auto rectColliderList = getComponentAll<RectCollider>();

		for (const auto & rectCollider : rectColliderList)
		{
			const BoundingPolygon2d& boundingPolygon2d = static_cast<const BoundingPolygon2d&>(rectCollider->getBodyBase());

			std::vector<Vector2> vertexArray = boundingPolygon2d.calculateLocalVertexs();
			vertexArray.push_back(boundingPolygon2d.calculateLocalVertexs().at(0));

			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					static_cast<int>(SystemBlendStateId::Alpha),
					static_cast<int>(SystemDepthStencilStateId::NotUseDepth),
					Color::white
					)
			);
		}

		auto polygon2dColliderList = getComponentAll<Polygon2dCollider>();

		for (const auto & polygon2dCollider : polygon2dColliderList)
		{
			const BoundingPolygon2d& boundingPolygon2d = static_cast<const BoundingPolygon2d&>(polygon2dCollider->getBodyBase());

			std::vector<Vector2> vertexArray = boundingPolygon2d.calculateLocalVertexs();
			vertexArray.push_back(boundingPolygon2d.calculateLocalVertexs().at(0));

			m_wireFrameDrawerArray.push_back(
				getGameObject()->createComponent<Line2DDrawer>(
					m_drawPriority,
					vertexArray,
					m_lineColor,
					static_cast<int>(SystemBlendStateId::Alpha),
					static_cast<int>(SystemDepthStencilStateId::NotUseDepth),
					Color::white
					)
			);
		}
	}

	void ColliderWireFrameDrawer2D::onEnable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const CfpPtr<Line2DDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(true); }
		);
	}

	void ColliderWireFrameDrawer2D::onDisable()
	{
		std::for_each(
			std::begin(m_wireFrameDrawerArray),
			std::end(m_wireFrameDrawerArray),
			[](const CfpPtr<Line2DDrawer>& wireFrameDrawer) { wireFrameDrawer->setActive(false); }
		);
	}
}