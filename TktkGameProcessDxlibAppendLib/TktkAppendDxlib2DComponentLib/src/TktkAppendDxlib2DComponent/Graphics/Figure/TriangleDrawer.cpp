#include "TktkAppendDxlib2DComponent/Graphics/Figure/TriangleDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	TriangleDrawer::TriangleDrawer(
		const Vector2 & relativeFirstPos,
		const Vector2 & relativeSecondPos,
		const Vector2 & relativeThirdPos,
		float lineThickness,
		bool isFill,
		const Color & triangleColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam,
		bool useAntialiasing
	)
		: ComponentBase(drawPriority)
		, m_relativeFirstPos(relativeFirstPos)
		, m_relativeSecondPos(relativeSecondPos)
		, m_relativeThirdPos(relativeThirdPos)
		, m_lineThickness(lineThickness)
		, m_isFill(isFill)
		, m_triangleColor(triangleColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_useAntialiasing(useAntialiasing)
	{
	}

	void TriangleDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.isNull())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void TriangleDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if(m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		Matrix3 selfPose = m_transform2D->calculateWorldMatrix();

		Vector2 pos1 = m_relativeFirstPos	* selfPose;
		Vector2 pos2 = m_relativeSecondPos	* selfPose;
		Vector2 pos3 = m_relativeThirdPos	* selfPose;

		if (m_useAntialiasing)
		{
			DrawTriangleAA(
				pos1.x, pos1.y,
				pos2.x, pos2.y,
				pos3.x, pos3.y,
				DXConverter::toUintColor(m_triangleColor),
				(m_isFill ? TRUE : FALSE),
				m_lineThickness
			);
		}
		else
		{
			DrawTriangle(
				static_cast<int>(pos1.x),
				static_cast<int>(pos1.y),
				static_cast<int>(pos2.x),
				static_cast<int>(pos2.y),
				static_cast<int>(pos3.x),
				static_cast<int>(pos3.y),
				DXConverter::toUintColor(m_triangleColor),
				(m_isFill ? TRUE : FALSE)
			);
		}
		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	const Vector2 & TriangleDrawer::getRelativeFirstPos() const
	{
		return m_relativeFirstPos;
	}

	void TriangleDrawer::setRelativeFirstPos(const Vector2 & relativeFirstPos)
	{
		m_relativeFirstPos = relativeFirstPos;
	}

	const Vector2 & TriangleDrawer::getRelativeSecondPos() const
	{
		return m_relativeSecondPos;
	}

	void TriangleDrawer::setRelativeSecondPos(const Vector2 & relativeSecondPos)
	{
		m_relativeSecondPos = relativeSecondPos;
	}

	const Vector2 & TriangleDrawer::getRelativeThirdPos() const
	{
		return m_relativeThirdPos;
	}

	void TriangleDrawer::setRelativeThirdPos(const Vector2 & relativeSecondPos)
	{
		m_relativeThirdPos = relativeSecondPos;
	}

	float TriangleDrawer::getLineThickness() const
	{
		return m_lineThickness;
	}

	void TriangleDrawer::setLineThickness(float lineThickness)
	{
		m_lineThickness = lineThickness;
	}

	bool TriangleDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void TriangleDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & TriangleDrawer::getTriangleColor() const
	{
		return m_triangleColor;
	}

	void TriangleDrawer::setTriangleColor(const Color & triangleColor)
	{
		m_triangleColor = triangleColor;
	}

	BlendMode TriangleDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void TriangleDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float TriangleDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void TriangleDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	bool TriangleDrawer::getUseAntialiasing() const
	{
		return m_useAntialiasing;
	}

	void TriangleDrawer::setUseAntialiasing(bool useAntialiasing)
	{
		m_useAntialiasing = useAntialiasing;
	}

	void TriangleDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void TriangleDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}