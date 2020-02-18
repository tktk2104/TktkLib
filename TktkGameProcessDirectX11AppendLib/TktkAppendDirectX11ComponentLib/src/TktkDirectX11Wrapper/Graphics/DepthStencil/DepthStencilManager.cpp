#include "TktkDirectX11Wrapper/Graphics/DepthStencil/DepthStencilManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<DepthStencilAssets> DepthStencilManager::m_assetsPtr;

	void DepthStencilManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new DepthStencilAssets());
	}

	void DepthStencilManager::create(int id, const Vector2 & useTextureSize)
	{
		m_assetsPtr->create(id, useTextureSize);
	}

	void DepthStencilManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void DepthStencilManager::clear()
	{
		m_assetsPtr->clear();
	}

	const DepthStencilData & DepthStencilManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}