#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilViewManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	CfpPtr<DepthStencilViewAssets> DepthStencilViewManager::m_assetsPtr;

	void DepthStencilViewManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<DepthStencilViewAssets>(true);

		create(SystemDepthStencilViewId::Basic, Window::getWindowSize());
	}

	void DepthStencilViewManager::clear()
	{
		m_assetsPtr->clear();
	}

	void DepthStencilViewManager::createImpl(int id, const Vector2 & useTextureSize)
	{
		m_assetsPtr->create(id, useTextureSize);
	}

	void DepthStencilViewManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const DepthStencilViewData & DepthStencilViewManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}