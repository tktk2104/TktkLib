#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/BlendStateAssets.h"

namespace tktk
{
	BlendStateAssets::~BlendStateAssets()
	{
		clear();
	}

	void BlendStateAssets::create(int id, const D3D11_BLEND_DESC & blendDesc)
	{
		erase(id);

		m_assets.emplace(id, blendDesc);
	}

	void BlendStateAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void BlendStateAssets::clear()
	{
		m_assets.clear();
	}

	BlendStateData * BlendStateAssets::getDataPtr(int id)
	{
		return &(m_assets.at(id));
	}
}