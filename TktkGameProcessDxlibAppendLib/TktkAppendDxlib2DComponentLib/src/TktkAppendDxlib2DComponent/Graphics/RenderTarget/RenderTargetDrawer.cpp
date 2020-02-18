#include "TktkAppendDxlib2DComponent/Graphics/RenderTarget/RenderTargetDrawer.h"

#include <DxLib.h>
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTarget.h"

namespace tktk
{
	RenderTargetDrawer::RenderTargetDrawer(
		int drawRenderTargetId,
		float drawPriority,
		BlendMode blendMode,
		float blendParam
	)
		: ComponentBase(drawPriority)
		, m_drawRenderTargetId(drawRenderTargetId)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
	{
	}

	void RenderTargetDrawer::draw() const
	{
		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));
	
		RenderTarget::drawRenderTargetTexture(m_drawRenderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}