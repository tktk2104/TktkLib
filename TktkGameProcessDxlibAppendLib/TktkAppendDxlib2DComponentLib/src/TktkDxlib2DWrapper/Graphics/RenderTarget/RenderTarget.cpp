#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTarget.h"

#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	int RenderTarget::getMainScreenHandle()
	{
		return RenderTargetManager::getMainScreenHandle();
	}

	void RenderTarget::setRenderTarget(int id)
	{
		RenderTargetManager::setRenderTarget(id);
	}

	void RenderTarget::unSetRenderTarget()
	{
		RenderTargetManager::unSetRenderTarget();
	}

	void RenderTarget::drawRenderTargetTexture(int id)
	{
		RenderTargetManager::drawRenderTargetTexture(id);
	}
}