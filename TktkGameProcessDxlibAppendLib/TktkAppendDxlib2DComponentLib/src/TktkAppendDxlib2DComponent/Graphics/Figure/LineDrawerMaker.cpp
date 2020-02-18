#include "TktkAppendDxlib2DComponent/Graphics/Figure/LineDrawerMaker.h"

namespace tktk
{
	LineDrawerMaker LineDrawerMaker::m_self;

	LineDrawerMaker & LineDrawerMaker::makeStart()
	{
		m_self = LineDrawerMaker();
		return m_self;
	}

	std::shared_ptr<LineDrawer> LineDrawerMaker::create()
	{
		auto lineDrawer = std::make_shared<LineDrawer>(
			m_relativeFirstPos,
			m_relativeSecondPos,
			m_lineThickness,
			m_lineColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam,
			m_useAntialiasing
			);

		if (m_useRenderTarget) lineDrawer->useRenderTarget(m_renderTargetId);

		return lineDrawer;
	}

	LineDrawerMaker & LineDrawerMaker::relativeFirstPos(const Vector2 & value)
	{
		m_relativeFirstPos = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::relativeSecondPos(const Vector2 & value)
	{
		m_relativeSecondPos = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::lineColor(const Color & value)
	{
		m_lineColor = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::useAntialiasing(bool value)
	{
		m_useAntialiasing = value;
		return *this;
	}

	LineDrawerMaker & LineDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}