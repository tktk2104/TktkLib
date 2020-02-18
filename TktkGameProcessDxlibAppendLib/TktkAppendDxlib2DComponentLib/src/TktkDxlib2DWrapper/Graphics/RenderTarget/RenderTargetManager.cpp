#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<RenderTargetUpdater> RenderTargetManager::m_renderTargetUpdater;

	void RenderTargetManager::setUp()
	{
		auto renderTargetUpdater = std::make_shared<RenderTargetUpdater>();
		ComponentFrameworkProcessor::addClass(renderTargetUpdater);
		m_renderTargetUpdater = renderTargetUpdater;
	}

	void RenderTargetManager::makeMainScreen(const Vector2 & screenSize)
	{
		m_renderTargetUpdater.lock()->makeMainScreen(screenSize);
	}

	int RenderTargetManager::getMainScreenHandle()
	{
		return m_renderTargetUpdater.lock()->getMainScreenHandle();
	}

	void RenderTargetManager::setRenderTarget(int id)
	{
		m_renderTargetUpdater.lock()->setRenderTarget(id);
	}

	void RenderTargetManager::unSetRenderTarget()
	{
		m_renderTargetUpdater.lock()->unSetRenderTarget();
	}

	void RenderTargetManager::drawRenderTargetTexture(int id)
	{
		m_renderTargetUpdater.lock()->drawRenderTargetTexture(id);
	}
}