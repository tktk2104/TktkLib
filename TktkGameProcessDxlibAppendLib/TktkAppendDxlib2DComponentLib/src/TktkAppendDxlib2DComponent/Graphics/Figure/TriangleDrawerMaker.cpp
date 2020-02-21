#include "TktkAppendDxlib2DComponent/Graphics/Figure/TriangleDrawerMaker.h"

namespace tktk
{
	TriangleDrawerMaker TriangleDrawerMaker::m_self;

	TriangleDrawerMaker & TriangleDrawerMaker::makeStart()
	{
		m_self = TriangleDrawerMaker();
		return m_self;
	}

	TriangleDrawer* TriangleDrawerMaker::create()
	{
		auto triangleDrawer = new TriangleDrawer(
			m_relativeFirstPos,
			m_relativeSecondPos,
			m_relativeThirdPos,
			m_lineThickness,
			m_isFill,
			m_triangleColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam,
			m_useAntialiasing
		);

		if (m_useRenderTarget) triangleDrawer->useRenderTarget(m_renderTargetId);

		return triangleDrawer;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::relativeFirstPos(const Vector2 & value)
	{
		m_relativeFirstPos = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::relativeSecondPos(const Vector2 & value)
	{
		m_relativeSecondPos = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::relativeThirdPos(const Vector2 & value)
	{
		m_relativeThirdPos = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::triangleColor(const Color & value)
	{
		m_triangleColor = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::useAntialiasing(bool value)
	{
		m_useAntialiasing = value;
		return *this;
	}

	TriangleDrawerMaker & TriangleDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}
}