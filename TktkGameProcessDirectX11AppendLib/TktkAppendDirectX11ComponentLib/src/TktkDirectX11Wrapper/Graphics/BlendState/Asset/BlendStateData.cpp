#include "TktkDirectX11Wrapper/Graphics/BlendState/Asset/BlendStateData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	BlendStateData::BlendStateData(const D3D11_BLEND_DESC & blendDesc)
	{
		Screen::getDevicePtr()->CreateBlendState(&blendDesc, &m_blendState);
	}

	BlendStateData::~BlendStateData()
	{
		if (m_blendState != nullptr)
		{
			m_blendState->Release();
		}
	}

	ID3D11BlendState * BlendStateData::getStatePtr() const
	{
		return m_blendState;
	}
}