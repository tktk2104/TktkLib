#include "TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTarget.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	void RenderTarget::createImpl(int id, ID3D11Texture2D * renderTargetTexture)
	{
		if (id <= 0)
		{
			throw std::runtime_error("RenderTargetId Fraud Value");
		}
		RenderTargetManager::create(id, renderTargetTexture);
	}

	void RenderTarget::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("RenderTargetId Fraud Value");
		}
		RenderTargetManager::erase(id);
	}

	const RenderTargetData & RenderTarget::getDataImpl(int id)
	{
		return RenderTargetManager::getData(id);
	}
}