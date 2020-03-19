#include "TktkDirectX11Wrapper/Graphics/RasterizerState/Asset/RasterizerStateData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	RasterizerStateData::RasterizerStateData(const D3D11_RASTERIZER_DESC & desc)
	{
		Screen::getDevicePtr()->CreateRasterizerState(&desc, &m_rasterizerStatePtr);
	}

	RasterizerStateData::~RasterizerStateData()
	{
		if (m_rasterizerStatePtr != nullptr)
		{
			m_rasterizerStatePtr->Release();
		}
	}

	void RasterizerStateData::setState() const
	{
		Screen::getDeviceContextPtr()->RSSetState(m_rasterizerStatePtr);
	}
}