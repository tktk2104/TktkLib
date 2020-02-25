#include "TktkAppendDxlib2DComponent/Graphics/Figure/CircleDrawerMaker.h"

namespace tktk
{
	CircleDrawerMaker CircleDrawerMaker::m_self;

	CircleDrawerMaker & CircleDrawerMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<CircleDrawer> CircleDrawerMaker::create()
	{
		auto circleDrawer = m_user->createComponent<CircleDrawer>(
			m_radius,
			m_localPosition,
			m_lineThickness,
			m_isFill,
			m_circleColor,
			m_drawPriority,
			m_blendMode,
			m_blendParam,
			m_useAntialiasing,
			m_vertexNum
			);

		if (m_useRenderTarget) circleDrawer->useRenderTarget(m_renderTargetId);

		return circleDrawer;
	}

	CircleDrawerMaker & CircleDrawerMaker::radius(float value)
	{
		m_radius = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::localPosition(const Vector2 & value)
	{
		m_localPosition = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::lineThickness(float value)
	{
		m_lineThickness = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::circleColor(const Color & value)
	{
		m_circleColor = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::useAntialiasing(bool value)
	{
		m_useAntialiasing = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::vertexNum(int value)
	{
		m_vertexNum = value;
		return *this;
	}

	CircleDrawerMaker & CircleDrawerMaker::renderTargetId(int value)
	{
		m_useRenderTarget = true;
		m_renderTargetId = value;
		return *this;
	}

	void CircleDrawerMaker::reset()
	{
		m_self.m_radius = 1.0f;
		m_self.m_localPosition = Vector2::zero;
		m_self.m_lineThickness = 1.0f;
		m_self.m_isFill = true;
		m_self.m_circleColor = Color::white;
		m_self.m_drawPriority = 0.0f;
		m_self.m_blendMode = BlendMode::Alpha;
		m_self.m_blendParam = 1.0f;
		m_self.m_useAntialiasing = true;
		m_self.m_vertexNum = 32;
		m_self.m_useRenderTarget = false;
		m_self.m_renderTargetId = -1;
	}
}