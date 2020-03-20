#include "TktkDirectX11Wrapper/Graphics/PixelShader/Asset/PixelShaderAssets.h"

#include <algorithm>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	PixelShaderAssets::~PixelShaderAssets()
	{
		clear();
	}

	void PixelShaderAssets::load(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(useConstantBufferIdArray, fileName)
		);
	}

	void PixelShaderAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void PixelShaderAssets::clear()
	{
		m_assets.clear();
	}

	const PixelShaderData & PixelShaderAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}