#include "TktkAppendDxlib2DComponent/Graphics/Figure/RectDrawerMaker.h"

namespace tktk
{
	RectDrawerMaker RectDrawerMaker::m_self;

	RectDrawerMaker & RectDrawerMaker::makeStart()
	{
		m_self = RectDrawerMaker();
		return m_self;
	}

	RectDrawer* RectDrawerMaker::create()
	{
		auto rectDrawer = new RectDrawer(
			m_rectSize,
			m_localPosition,
			m_lineThickness,
			m_isFill,
			m_rectColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam,
			m_useAntialiasing
		);

		if (m_useRenderTarget) rectDrawer->useRenderTarget(m_renderTargetId);

		return rectDrawer;
	}

	RectDrawerMaker & RectDrawerMaker::rectSize(const Vector2 & value)
	{
		m_rectSize = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::rectColor(const Color & value)
	{
		m_rectColor = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::useAntialiasing(bool value)
	{
		m_useAntialiasing = value;
		return *this;
	}

	RectDrawerMaker & RectDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}