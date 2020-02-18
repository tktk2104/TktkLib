#include "TktkDirectX11Wrapper/Graphics/RenderTarget/Asset/RenderTargetData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	RenderTargetData::RenderTargetData(ID3D11Texture2D * renderTargetTexturePtr)
	{
		Screen::getDevicePtr()->CreateRenderTargetView(renderTargetTexturePtr, NULL, &m_viewPtr);
	}

	RenderTargetData::~RenderTargetData()
	{
		if (m_viewPtr != nullptr)
		{
			m_viewPtr->Release();
		}
	}

	ID3D11RenderTargetView * RenderTargetData::getViewPtr() const
	{
		return m_viewPtr;
	}
}