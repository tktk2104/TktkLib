#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<RenderTargetUpdater> RenderTargetManager::m_renderTargetUpdater;

	void RenderTargetManager::setUp()
	{
		m_renderTargetUpdater = ComponentFrameworkProcessor::addClass(true, new RenderTargetUpdater());;
	}

	void RenderTargetManager::makeMainScreen(const Vector2 & screenSize)
	{
		m_renderTargetUpdater->makeMainScreen(screenSize);
	}

	int RenderTargetManager::getMainScreenHandle()
	{
		return m_renderTargetUpdater->getMainScreenHandle();
	}

	void RenderTargetManager::setRenderTarget(int id)
	{
		m_renderTargetUpdater->setRenderTarget(id);
	}

	void RenderTargetManager::unSetRenderTarget()
	{
		m_renderTargetUpdater->unSetRenderTarget();
	}

	void RenderTargetManager::drawRenderTargetTexture(int id)
	{
		m_renderTargetUpdater->drawRenderTargetTexture(id);
	}
}