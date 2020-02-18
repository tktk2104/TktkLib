#include "TktkDirectX11Wrapper/Graphics/RenderTarget/Asset/RenderTargetAssets.h"

#include <algorithm>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/RenderTarget/Asset/SystemRenderTargetId.h"

namespace tktk
{
	RenderTargetAssets::RenderTargetAssets()
	{
		ID3D11Texture2D *backBufferTexture;
		Screen::getSwapChainPtr()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		create(SYSTEM_RENDER_TARGET_BACK_BUFFER, backBufferTexture);
		backBufferTexture->Release();
	}

	RenderTargetAssets::~RenderTargetAssets()
	{
		clear();
	}

	void RenderTargetAssets::create(int id, ID3D11Texture2D * renderTargetTexture)
	{
		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(renderTargetTexture)
		);
	}

	void RenderTargetAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void RenderTargetAssets::clear()
	{
		m_assets.clear();
	}

	const RenderTargetData & RenderTargetAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}