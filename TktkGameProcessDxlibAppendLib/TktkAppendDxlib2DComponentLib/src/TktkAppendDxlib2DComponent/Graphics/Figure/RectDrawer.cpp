#include "TktkAppendDxlib2DComponent/Graphics/Figure/RectDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	RectDrawer::RectDrawer(
		const Vector2 & rectSize,
		const Vector2 & localPosition,
		float lineThickness,
		bool isFill,
		const Color & rectColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam,
		bool useAntialiasing
	)
		: ComponentBase(drawPriority)
		, m_rectSize(rectSize)
		, m_localPosition(localPosition)
		, m_lineThickness(lineThickness)
		, m_isFill(isFill)
		, m_rectColor(rectColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_useAntialiasing(useAntialiasing)
	{
	}

	void RectDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void RectDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		Matrix3 selfPose = m_transform2D->calculateWorldMatrix();

		Vector2 pos1 = (Vector2(-m_rectSize.x * 0.5f, -m_rectSize.y * 0.5f) + m_localPosition) * selfPose;
		Vector2 pos2 = (Vector2( m_rectSize.x * 0.5f, -m_rectSize.y * 0.5f) + m_localPosition) * selfPose;
		Vector2 pos3 = (Vector2( m_rectSize.x * 0.5f,  m_rectSize.y * 0.5f) + m_localPosition) * selfPose;
		Vector2 pos4 = (Vector2(-m_rectSize.x * 0.5f,  m_rectSize.y * 0.5f) + m_localPosition) * selfPose;

		if (m_useAntialiasing)
		{
			DxLib::DrawQuadrangleAA(
				pos1.x, pos1.y,
				pos2.x, pos2.y,
				pos3.x, pos3.y,
				pos4.x, pos4.y,
				DXConverter::toUintColor(m_rectColor),
				(m_isFill) ? TRUE : FALSE,
				m_lineThickness
			);
		}
		else
		{
			DxLib::DrawQuadrangle(
				static_cast<int>(pos1.x),
				static_cast<int>(pos1.y),
				static_cast<int>(pos2.x),
				static_cast<int>(pos2.y),
				static_cast<int>(pos3.x),
				static_cast<int>(pos3.y),
				static_cast<int>(pos4.x),
				static_cast<int>(pos4.y),
				DXConverter::toUintColor(m_rectColor),
				(m_isFill) ? TRUE : FALSE
			);
		}

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	const Vector2 & RectDrawer::getRectSize() const
	{
		return m_rectSize;
	}

	void RectDrawer::setRectSize(const Vector2 & rectSize)
	{
		m_rectSize = rectSize;
	}

	const Vector2 & RectDrawer::getLocalPosition() const
	{
		return m_localPosition;
	}

	void RectDrawer::setLocalPosition(const Vector2 & localPosition)
	{
		m_localPosition = localPosition;
	}

	float RectDrawer::getLineThickness() const
	{
		return m_lineThickness;
	}

	void RectDrawer::setLineThickness(float lineThickness)
	{
		m_lineThickness = lineThickness;
	}

	bool RectDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void RectDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & RectDrawer::getRectColor() const
	{
		return m_rectColor;
	}

	void RectDrawer::setRectColor(const Color & rectColor)
	{
		m_rectColor = rectColor;
	}

	BlendMode RectDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void RectDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float RectDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void RectDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	bool RectDrawer::getUseAntialiasing() const
	{
		return m_useAntialiasing;
	}

	void RectDrawer::setUseAntialiasing(bool useAntialiasing)
	{
		m_useAntialiasing = useAntialiasing;
	}

	void RectDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void RectDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}