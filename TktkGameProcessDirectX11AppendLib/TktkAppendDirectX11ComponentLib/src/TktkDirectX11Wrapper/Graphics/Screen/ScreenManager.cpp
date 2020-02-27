#include "TktkDirectX11Wrapper/Graphics/Screen/ScreenManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

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

	void ScreenManager::setRenderTargetsAndDepthStencilView(const std::vector<int>& renderTargetIdArray, int depthStencilViewId)
	{
		m_updaterPtr->setRenderTargetsAndDepthStencilView(renderTargetIdArray, depthStencilViewId);
	}
}