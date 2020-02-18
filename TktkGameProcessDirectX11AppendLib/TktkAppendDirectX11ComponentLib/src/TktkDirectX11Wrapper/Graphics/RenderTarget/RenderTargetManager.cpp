#include "TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTargetManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<RenderTargetAssets> RenderTargetManager::m_assetsPtr;

	void RenderTargetManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new RenderTargetAssets());
	}

	void RenderTargetManager::create(int id, ID3D11Texture2D * renderTargetTexture)
	{
		m_assetsPtr->create(id, renderTargetTexture);
	}

	void RenderTargetManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void RenderTargetManager::clear()
	{
		m_assetsPtr->clear();
	}

	const RenderTargetData & RenderTargetManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}