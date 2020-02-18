#include "TktkDirectX11Wrapper/Graphics/DepthStencil/Asset/DepthStencilAssets.h"

#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencil/Asset/SystemDepthStencilId.h"

namespace tktk
{
	DepthStencilAssets::DepthStencilAssets()
	{
		create(SYSTEM_DEPTH_STENCIL_BASIC, Window::getWindowSize());
	}

	DepthStencilAssets::~DepthStencilAssets()
	{
		clear();
	}

	void DepthStencilAssets::create(int id, const Vector2 & useTextureSize)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(useTextureSize)
		);
	}

	void DepthStencilAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void DepthStencilAssets::clear()
	{
		m_assets.clear();
	}

	const DepthStencilData & DepthStencilAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}