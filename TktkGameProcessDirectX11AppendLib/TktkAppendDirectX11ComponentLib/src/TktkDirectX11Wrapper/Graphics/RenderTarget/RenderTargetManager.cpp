#include "TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTargetManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/RenderTarget/Asset/SystemRenderTargetId.h"

namespace tktk
{
	CfpPtr<RenderTargetAssets> RenderTargetManager::m_assetsPtr;

	void RenderTargetManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new RenderTargetAssets());
		ID3D11Texture2D *backBufferTexture;
		Screen::getSwapChainPtr()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		create(SystemRenderTargetId::Basic, backBufferTexture);
		backBufferTexture->Release();
	}

	void RenderTargetManager::clear()
	{
		m_assetsPtr->clear();
	}

	void RenderTargetManager::createImpl(int id, ID3D11Texture2D * renderTargetTexture)
	{
		m_assetsPtr->create(id, renderTargetTexture);
	}

	void RenderTargetManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const RenderTargetData & RenderTargetManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}