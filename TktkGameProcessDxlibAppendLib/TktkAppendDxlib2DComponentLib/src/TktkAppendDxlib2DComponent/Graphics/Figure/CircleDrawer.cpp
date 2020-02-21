#include "TktkAppendDxlib2DComponent/Graphics/Figure/CircleDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	CircleDrawer::CircleDrawer(
		float radius,
		const Vector2 & localPosition,
		float lineThickness,
		bool isFill,
		const Color & circleColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam,
		bool useAntialiasing,
		int vertexNum
	)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_lineThickness(lineThickness)
		, m_isFill(isFill)
		, m_circleColor(circleColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_useAntialiasing(useAntialiasing)
		, m_vertexNum(vertexNum)
	{
	}

	void CircleDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void CircleDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		const Vector2& selfPos = m_transform2D->getWorldPosition();
		float scaleX = m_transform2D->getWorldScaleRate().x;

		if (m_useAntialiasing)
		{
			DxLib::DrawCircleAA(
				selfPos.x + m_localPosition.x,
				selfPos.y + m_localPosition.y,
				m_radius * scaleX,
				m_vertexNum,
				DXConverter::toUintColor(m_circleColor),
				(m_isFill ? TRUE : FALSE),
				m_lineThickness
			);
		}
		else
		{
			DxLib::DrawCircle(
				static_cast<int>(selfPos.x + m_localPosition.x),
				static_cast<int>(selfPos.y + m_localPosition.y),
				static_cast<int>(m_radius * scaleX),
				DXConverter::toUintColor(m_circleColor),
				(m_isFill ? TRUE : FALSE),
				static_cast<int>(m_lineThickness)
			);
		}
		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	float CircleDrawer::getRadius() const
	{
		return m_radius;
	}

	void CircleDrawer::setRadius(float radius)
	{
		m_radius = radius;
	}

	const Vector2 & CircleDrawer::getLocalPosition() const
	{
		return m_localPosition;
	}

	void CircleDrawer::setLocalPosition(const Vector2 & localPosition)
	{
		m_localPosition = localPosition;
	}

	float CircleDrawer::getLineThickness() const
	{
		return m_lineThickness;
	}

	void CircleDrawer::setLineThickness(float lineThickness)
	{
		m_lineThickness = lineThickness;
	}

	bool CircleDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void CircleDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & CircleDrawer::getCircleColor() const
	{
		return m_circleColor;
	}

	void CircleDrawer::setCircleColor(const Color & circleColor)
	{
		m_circleColor = circleColor;
	}

	BlendMode CircleDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void CircleDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float CircleDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void CircleDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	bool CircleDrawer::getUseAntialiasing() const
	{
		return m_useAntialiasing;
	}

	void CircleDrawer::setUseAntialiasing(bool useAntialiasing)
	{
		m_useAntialiasing = useAntialiasing;
	}

	int CircleDrawer::getVertexNum() const
	{
		return m_vertexNum;
	}

	void CircleDrawer::setVertexNum(int vertexNum)
	{
		m_vertexNum = vertexNum;
	}

	void CircleDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void CircleDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}