#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilViewManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<DepthStencilViewAssets> DepthStencilViewManager::m_assetsPtr;

	void DepthStencilViewManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<DepthStencilViewAssets>(true);
	}

	void DepthStencilViewManager::create(int id, const Vector2 & useTextureSize)
	{
		m_assetsPtr->create(id, useTextureSize);
	}

	void DepthStencilViewManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void DepthStencilViewManager::clear()
	{
		m_assetsPtr->clear();
	}

	const DepthStencilViewData & DepthStencilViewManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}