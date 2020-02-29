#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/DepthStencilStateAssets.h"

namespace tktk
{
	DepthStencilStateAssets::~DepthStencilStateAssets()
	{
		clear();
	}

	void DepthStencilStateAssets::create(int id, const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		erase(id);

		m_assets.emplace(id, depthStencilDesc);
	}

	void DepthStencilStateAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void DepthStencilStateAssets::clear()
	{
		m_assets.clear();
	}

	DepthStencilStateData * DepthStencilStateAssets::getData(int id)
	{
		return &(m_assets.at(id));
	}
}