#include "TktkDirectX11Wrapper/Graphics/Screen/ScreenManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkDirectX11Wrapper/Graphics/DepthStencilView/Asset/SystemDepthStencilViewId.h>
#include <TktkDirectX11Wrapper/Graphics/RenderTarget/Asset/SystemRenderTargetId.h>

namespace tktk
{
	CfpPtr<ScreenUpdater> ScreenManager::m_updaterPtr;

	void ScreenManager::setUp(bool fullScreen)
	{
		m_updaterPtr = ComponentFrameworkProcessor::addClass(true, new ScreenUpdater(fullScreen));
	}

	IDXGISwapChain * ScreenManager::getSwapChainPtr()
	{
		return m_updaterPtr->getSwapChainPtr();
	}

	ID3D11Device * ScreenManager::getDevicePtr()
	{
		return m_updaterPtr->getDevicePtr();
	}

	ID3D11DeviceContext * ScreenManager::getDeviceContextPtr()
	{
		return m_updaterPtr->getDeviceContextPtr();
	}

	void ScreenManager::setBackgroundColor(const Color & color)
	{
		m_updaterPtr->setBackgroundColor(color);
	}

	void ScreenManager::setDepthStencilViewAndRenderTargetsImpl(int depthStencilViewId, const std::vector<int>& renderTargetIdArray)
	{
		m_updaterPtr->setDepthStencilViewAndRenderTargets(depthStencilViewId, renderTargetIdArray);
	}
}