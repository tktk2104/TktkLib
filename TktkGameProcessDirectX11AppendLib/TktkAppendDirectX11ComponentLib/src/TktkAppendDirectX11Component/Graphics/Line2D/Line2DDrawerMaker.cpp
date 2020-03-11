#include "TktkAppendDirectX11Component/Graphics/Line2D/Line2DDrawerMaker.h"

namespace tktk
{
	Line2DDrawerMaker Line2DDrawerMaker::m_self;

	Line2DDrawerMaker & Line2DDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = Line2DDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<Line2DDrawer> Line2DDrawerMaker::create()
	{
		return m_user->createComponent<Line2DDrawer>(
			m_drawPriority,
			m_lineVertexArray,
			m_lineColor,
			m_blendStateId,
			m_depthStencilStateId,
			m_blendRate
			);
	}

	Line2DDrawerMaker & Line2DDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineVertexArray(const std::vector<Vector2>& value)
	{
		m_lineVertexArray = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineColor(const Color & value)
	{
		m_lineColor = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::blendRate(const Color & value)
	{
		m_blendRate = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::blendStateIdImpl(int value)
	{
		m_blendStateId = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::depthStencilStateIdImpl(int value)
	{
		m_depthStencilStateId = value;
		return *this;
	}
}