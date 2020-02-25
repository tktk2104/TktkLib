#include "TktkAppendDxlib2DComponent/Graphics/Figure/OvalDrawerMaker.h"

namespace tktk
{
	OvalDrawerMaker OvalDrawerMaker::m_self;

	OvalDrawerMaker & OvalDrawerMaker::makeStart(GameObjectPtr user)
	{
		reset();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<OvalDrawer> OvalDrawerMaker::create()
	{
		auto ovalDrawer = m_user->createComponent<OvalDrawer>(
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

	void OvalDrawerMaker::reset()
	{
		m_self.m_ovalSize = Vector2::one;
		m_self.m_localPosition = Vector2::zero;
		m_self.m_lineThickness = 1.0f;
		m_self.m_isFill = true;
		m_self.m_ovalColor = Color::white;
		m_self.m_drawPriority = 0.0f;
		m_self.m_blendMode = BlendMode::Alpha;
		m_self.m_blendParam = 1.0f;
		m_self.m_useAntialiasing = true;
		m_self.m_vertexNum = 32;
		m_self.m_useRenderTarget = false;
		m_self.m_renderTargetId = -1;
	}
}