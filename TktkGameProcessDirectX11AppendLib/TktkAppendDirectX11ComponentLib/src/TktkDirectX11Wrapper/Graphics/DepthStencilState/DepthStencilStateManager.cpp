#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilStateManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<DepthStencilStateAssets> DepthStencilStateManager::m_assetsPtr;

	void DepthStencilStateManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<DepthStencilStateAssets>(true);
	}

	void DepthStencilStateManager::create(int id, const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		m_assetsPtr->create(id, depthStencilDesc);
	}

	void DepthStencilStateManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void DepthStencilStateManager::clear()
	{
		m_assetsPtr->clear();
	}

	DepthStencilStateData * DepthStencilStateManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}