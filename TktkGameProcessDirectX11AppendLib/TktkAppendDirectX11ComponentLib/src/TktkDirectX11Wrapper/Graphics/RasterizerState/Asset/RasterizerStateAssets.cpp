#include "TktkDirectX11Wrapper/Graphics/RasterizerState/Asset/RasterizerStateAssets.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	RasterizerStateAssets::~RasterizerStateAssets()
	{
		clear();
	}

	void RasterizerStateAssets::create(int id, const D3D11_RASTERIZER_DESC & desc)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(desc)
		);
	}

	void RasterizerStateAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void RasterizerStateAssets::clear()
	{
		m_assets.clear();
	}

	const RasterizerStateData & RasterizerStateAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}