#include "TktkAppendDxlib2DComponent/Graphics/Figure/Polygon2DDrawerMaker.h"

namespace tktk
{
	Polygon2DDrawerMaker Polygon2DDrawerMaker::m_self;

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<Polygon2DDrawer> Polygon2DDrawerMaker::create()
	{
		auto polygon2DDrawer = m_user->createComponent<Polygon2DDrawer>(
			m_vertexs,
			m_lineThickness,
			m_isFill,
			m_polygonColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam
			);

		if (m_useRenderTarget) polygon2DDrawer->useRenderTarget(m_renderTargetId);

		return polygon2DDrawer;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::vertexs(const std::vector<Vector2>& value)
	{
		m_vertexs = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::polygonColor(const Color & value)
	{
		m_polygonColor = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	Polygon2DDrawerMaker & Polygon2DDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}

	void Polygon2DDrawerMaker::reset()
	{
		m_self.m_vertexs = {};
		m_self.m_lineThickness = 1.0f;
		m_self.m_isFill = true;
		m_self.m_polygonColor = Color::white;
		m_self.m_drawPriority = 0.0f;
		m_self.m_blendMode = BlendMode::Alpha;
		m_self.m_blendParam = 1.0f;
		m_self.m_useRenderTarget = false;
		m_self.m_renderTargetId = -1;
	}
}