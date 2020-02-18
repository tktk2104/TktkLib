#include "TktkDirectX11Wrapper/Graphics/ViewPort/Asset/ViewPortData.h"

namespace tktk
{
	ViewPortData::ViewPortData(const Vector2 & position, const Vector2 & size)
	{
		m_viewPort.TopLeftX = position.x;
		m_viewPort.TopLeftY = position.y;
		m_viewPort.Width = size.x;
		m_viewPort.Height = size.y;
		m_viewPort.MinDepth = 0.0f;
		m_viewPort.MaxDepth = 1.0f;
	}

	ViewPortData::~ViewPortData()
	{
	}

	const D3D11_VIEWPORT & ViewPortData::getViewPort() const
	{
		return m_viewPort;
	}
}