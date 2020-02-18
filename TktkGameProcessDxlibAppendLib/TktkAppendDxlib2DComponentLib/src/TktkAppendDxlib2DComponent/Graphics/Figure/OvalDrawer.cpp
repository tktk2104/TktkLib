#include "TktkAppendDxlib2DComponent/Graphics/Figure/OvalDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	OvalDrawer::OvalDrawer(
		const Vector2 & ovalSize,
		const Vector2 & localPosition,
		float lineThickness,
		bool isFill,
		const Color & ovalColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam,
		bool useAntialiasing,
		int vertexNum
	)
		: ComponentBase(drawPriority)
		, m_ovalSize(ovalSize)
		, m_localPosition(localPosition)
		, m_lineThickness(lineThickness)
		, m_isFill(isFill)
		, m_ovalColor(ovalColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
		, m_useAntialiasing(useAntialiasing)
		, m_vertexNum(vertexNum)
	{
	}

	void OvalDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void OvalDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		const Vector2& selfPos = m_transform2D.lock()->getWorldPosition();
		const Vector2& selfScale = m_transform2D.lock()->getWorldScaleRate();

		if (m_useAntialiasing)
		{
			DxLib::DrawOvalAA(
				selfPos.x + m_localPosition.x,
				selfPos.y + m_localPosition.y,
				m_ovalSize.x * selfScale.x,
				m_ovalSize.y * selfScale.y,
				m_vertexNum,
				DXConverter::toUintColor(m_ovalColor),
				m_isFill,
				m_lineThickness
			);
		}
		else
		{
			DxLib::DrawOval(
				static_cast<int>(selfPos.x + m_localPosition.x),
				static_cast<int>(selfPos.y + m_localPosition.y),
				static_cast<int>(m_ovalSize.x * selfScale.x),
				static_cast<int>(m_ovalSize.y * selfScale.y),
				DXConverter::toUintColor(m_ovalColor),
				m_isFill,
				static_cast<int>(m_lineThickness)
			);
		}
		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	const Vector2 & OvalDrawer::getOvalSize() const
	{
		return m_ovalSize;
	}

	void OvalDrawer::setOvalSize(const Vector2 & ovalSize)
	{
		m_ovalSize = ovalSize;
	}

	const Vector2 & OvalDrawer::getLocalPosition() const
	{
		return m_localPosition;
	}

	void OvalDrawer::setLocalPosition(const Vector2 & localPosition)
	{
		m_localPosition = localPosition;
	}

	bool OvalDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void OvalDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & OvalDrawer::getOvalColor() const
	{
		return m_ovalColor;
	}

	void OvalDrawer::setOvalColor(const Color & ovalColor)
	{
		m_ovalColor = ovalColor;
	}

	BlendMode OvalDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void OvalDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float OvalDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void OvalDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	bool OvalDrawer::getUseAntialiasing() const
	{
		return m_useAntialiasing;
	}

	void OvalDrawer::setUseAntialiasing(bool useAntialiasing)
	{
		m_useAntialiasing = useAntialiasing;
	}

	int OvalDrawer::getVertexNum() const
	{
		return m_vertexNum;
	}

	void OvalDrawer::setVertexNum(int vertexNum)
	{
		m_vertexNum = vertexNum;
	}

	void OvalDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void OvalDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}