#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendStateManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<BlendStateAssets> BlendStateManager::m_assetsPtr;

	void BlendStateManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<BlendStateAssets>(true);
	}

	void BlendStateManager::create(int id, const D3D11_BLEND_DESC & blendDesc)
	{
		m_assetsPtr->create(id, blendDesc);
	}

	void BlendStateManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void BlendStateManager::clear()
	{
		m_assetsPtr->clear();
	}

	BlendStateData * BlendStateManager::getDataPtr(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}