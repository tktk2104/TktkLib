#include "TktkAppendDxlib2DComponent/Graphics/RenderTarget/RenderTargetDrawerMaker.h"

namespace tktk
{
	RenderTargetDrawerMaker RenderTargetDrawerMaker::m_self;

	RenderTargetDrawerMaker & RenderTargetDrawerMaker::makeStart()
	{
		m_self = RenderTargetDrawerMaker();
		return m_self;
	}

	std::shared_ptr<RenderTargetDrawer> RenderTargetDrawerMaker::create()
	{
		return std::make_shared<RenderTargetDrawer>(
			m_drawRenderTargetId,
			m_drawPriority,
			m_blendMode,
			m_blendParam
			);
	}

	RenderTargetDrawerMaker & RenderTargetDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	RenderTargetDrawerMaker & RenderTargetDrawerMaker::drawRenderTargetId(int value)
	{
		m_drawRenderTargetId = value;
		return *this;
	}

	RenderTargetDrawerMaker & RenderTargetDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	RenderTargetDrawerMaker & RenderTargetDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}
}