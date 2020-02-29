#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/Asset/DepthStencilStateData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	DepthStencilStateData::DepthStencilStateData(const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		Screen::getDevicePtr()->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	}

	DepthStencilStateData::~DepthStencilStateData()
	{
		if (m_depthStencilState != nullptr)
		{
			m_depthStencilState->Release();
		}
	}

	ID3D11DepthStencilState * DepthStencilStateData::getStatePtr() const
	{
		return m_depthStencilState;
	}
}