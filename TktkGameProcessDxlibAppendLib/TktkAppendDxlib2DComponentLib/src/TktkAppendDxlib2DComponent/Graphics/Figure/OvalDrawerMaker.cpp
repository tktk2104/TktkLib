#include "TktkAppendDxlib2DComponent/Graphics/Figure/OvalDrawerMaker.h"

namespace tktk
{
	OvalDrawerMaker OvalDrawerMaker::m_self;

	OvalDrawerMaker & OvalDrawerMaker::makeStart()
	{
		m_self = OvalDrawerMaker();
		return m_self;
	}

	std::shared_ptr<OvalDrawer> OvalDrawerMaker::create()
	{
		auto ovalDrawer = std::make_shared<OvalDrawer>(
			m_ovalSize,
			m_localPosition,
			m_lineThickness,
			m_isFill,
			m_ovalColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam,
			m_useAntialiasing,
			m_vertexNum
			);

		if (m_useRenderTarget) ovalDrawer->useRenderTarget(m_renderTargetId);

		return ovalDrawer;
	}

	OvalDrawerMaker & OvalDrawerMaker::ovalSize(const Vector2 & value)
	{
		m_ovalSize = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::ovalColor(const Color & value)
	{
		m_ovalColor = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::useAntialiasing(bool value)
	{
		m_useAntialiasing = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::vertexNum(int value)
	{
		m_vertexNum = value;
		return *this;
	}

	OvalDrawerMaker & OvalDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}