#include "TktkDirectX11Wrapper/Graphics/ViewPort/Asset/ViewPortAssets.h"

#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"
#include "TktkDirectX11Wrapper/Graphics/ViewPort/Asset/SystemViewPortId.h"

namespace tktk
{
	ViewPortAssets::ViewPortAssets()
	{
		create(SYSTEM_VIEW_PORT_DEFAULT, Vector2::zero, Window::getWindowSize());
		Screen::getDeviceContextPtr()->RSSetViewports(1, &getData(SYSTEM_VIEW_PORT_DEFAULT).getViewPort());
	}

	ViewPortAssets::~ViewPortAssets()
	{
		clear();
	}

	void ViewPortAssets::create(int id, const Vector2 & position, const Vector2 & size)
	{
		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(position, size)
		);
	}

	void ViewPortAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void ViewPortAssets::clear()
	{
		m_assets.clear();
	}

	const ViewPortData & ViewPortAssets::getData(int id) const
	{
		return m_assets.at(id);
	}
}