#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/Asset/DepthStencilViewAssets.h"

#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	DepthStencilViewAssets::DepthStencilViewAssets()
	{
		create(SYSTEM_DEPTH_STENCIL_VIEW_BASIC, Window::getWindowSize());
	}

	DepthStencilViewAssets::~DepthStencilViewAssets()
	{
		clear();
	}

	void DepthStencilViewAssets::create(int id, const Vector2 & useTextureSize)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(useTextureSize)
		);
	}

	void DepthStencilViewAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void DepthStencilViewAssets::clear()
	{
		m_assets.clear();
	}

	const DepthStencilViewData & DepthStencilViewAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}