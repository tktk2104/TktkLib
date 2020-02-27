#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/ScreenManager.h"

namespace tktk
{
	IDXGISwapChain * Screen::getSwapChainPtr()
	{
		return ScreenManager::getSwapChainPtr();
	}

	ID3D11Device * Screen::getDevicePtr()
	{
		return ScreenManager::getDevicePtr();
	}

	ID3D11DeviceContext * Screen::getDeviceContextPtr()
	{
		return ScreenManager::getDeviceContextPtr();
	}

	void Screen::setBackgroundColor(const Color & color)
	{
		ScreenManager::setBackgroundColor(color);
	}

	void Screen::setRenderTargetsAndDepthStencilView(const std::vector<int>& renderTargetIdArray, int depthStencilViewId)
	{
		ScreenManager::setRenderTargetsAndDepthStencilView(renderTargetIdArray, depthStencilViewId);
	}
}