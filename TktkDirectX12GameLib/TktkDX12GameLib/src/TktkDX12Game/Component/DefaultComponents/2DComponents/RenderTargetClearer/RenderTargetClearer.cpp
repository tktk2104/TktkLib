#include "TktkDX12Game/Component/DefaultComponents/2DComponents/RenderTargetClearer/RenderTargetClearer.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	RenderTargetClearer::RenderTargetClearer(unsigned int clearRenderTargetId, const tktkMath::Color& clearColor)
		: ComponentBase(10.0f)
		, m_clearRenderTargetId(clearRenderTargetId)
		, m_clearColor(clearColor)
	{
	}

	void RenderTargetClearer::draw() const
	{
		DX12GameManager::clearRenderTarget(m_clearRenderTargetId, 0U, m_clearColor);
	}
}