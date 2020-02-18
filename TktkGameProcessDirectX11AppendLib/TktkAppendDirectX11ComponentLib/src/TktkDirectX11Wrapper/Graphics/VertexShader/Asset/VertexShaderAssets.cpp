#include "TktkDirectX11Wrapper/Graphics/VertexShader/Asset/VertexShaderAssets.h"

#include <stdexcept>
#include <algorithm>
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	VertexShaderAssets::~VertexShaderAssets()
	{
		clear();
	}

	void VertexShaderAssets::load(
		int id,
		int useConstantBufferId,
		const std::string & fileName,
		const std::vector<D3D11_INPUT_ELEMENT_DESC> & vertexLayout
	)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(useConstantBufferId, fileName, vertexLayout)
		);
	}

	void VertexShaderAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void VertexShaderAssets::clear()
	{
		m_assets.clear();
	}

	const VertexShaderData & VertexShaderAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}