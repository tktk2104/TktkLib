#include "TktkAppendDxlib2DComponent/Graphics/Figure/LineDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	LineDrawer::LineDrawer(
		const Vector2 & relativeFirstPos,
		const Vector2 & relativeSecondPos,
		float lineThickness,
		const Color & lineColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam,
		bool useAntialiasing
	)
		: ComponentBase(drawPriority)
		, m_relativeFirstPos(relativeFirstPos)
		, m_relativeSecondPos(relativeSecondPos)
		, m_lineThickness(lineThickness)
		, m_lineColor(lineColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_useAntialiasing(useAntialiasing)
	{
	}

	void LineDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void LineDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		Matrix3 selfPose = m_transform2D->calculateWorldMatrix();

		Vector2 pos1 = m_relativeFirstPos	* selfPose;
		Vector2 pos2 = m_relativeSecondPos	* selfPose;

		if (m_useAntialiasing)
		{
			DxLib::DrawLineAA(
				pos1.x,
				pos1.y,
				pos2.x,
				pos2.y,
				DXConverter::toUintColor(m_lineColor),
				m_lineThickness
			);
		}
		else
		{
			DxLib::DrawLine(
				static_cast<int>(pos1.x),
				static_cast<int>(pos1.y),
				static_cast<int>(pos2.x),
				static_cast<int>(pos2.y),
				DXConverter::toUintColor(m_lineColor),
				static_cast<int>(m_lineThickness)
			);
		}
		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	const Vector2 & LineDrawer::getRelativeFirstPos() const
	{
		return m_relativeFirstPos;
	}

	void LineDrawer::setRelativeFirstPos(const Vector2 & relativeFirstPos)
	{
		m_relativeFirstPos = relativeFirstPos;
	}

	const Vector2 & LineDrawer::getRelativeSecondPos() const
	{
		return m_relativeSecondPos;
	}

	void LineDrawer::setRelativeSecondPos(const Vector2 & relativeSecondPos)
	{
		m_relativeSecondPos = relativeSecondPos;
	}

	float LineDrawer::getLineThickness() const
	{
		return m_lineThickness;
	}

	void LineDrawer::setLineThickness(float lineThickness)
	{
		m_lineThickness = lineThickness;
	}

	const Color & LineDrawer::getLineColor() const
	{
		return m_lineColor;
	}

	void LineDrawer::setLineColor(const Color & lineColor)
	{
		m_lineColor = lineColor;
	}

	BlendMode LineDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void LineDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float LineDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void LineDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	bool LineDrawer::getUseAntialiasing() const
	{
		return m_useAntialiasing;
	}

	void LineDrawer::setUseAntialiasing(bool useAntialiasing)
	{
		m_useAntialiasing = useAntialiasing;
	}

	void LineDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void LineDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}