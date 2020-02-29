#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/Asset/DepthStencilViewData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	DepthStencilViewData::DepthStencilViewData(const Vector2 & useTextureSize)
	{
		// デプスステンシルバッファ用のテクスチャを生成
		D3D11_TEXTURE2D_DESC dtd{};
		dtd.Width = static_cast<int>(useTextureSize.x);
		dtd.Height = static_cast<int>(useTextureSize.y);
		dtd.MipLevels = 1;
		dtd.ArraySize = 1;
		dtd.Format = DXGI_FORMAT_D32_FLOAT;
		dtd.SampleDesc.Count = 1;
		dtd.SampleDesc.Quality = 0;
		dtd.Usage = D3D11_USAGE_DEFAULT;
		dtd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dtd.CPUAccessFlags = 0;
		dtd.MiscFlags = 0;
		Screen::getDevicePtr()->CreateTexture2D(&dtd, NULL, &m_useTexturePtr);

		// デプス・ステンシルバッファビューの生成
		Screen::getDevicePtr()->CreateDepthStencilView(m_useTexturePtr, NULL, &m_viewPtr);
	}

	DepthStencilViewData::~DepthStencilViewData()
	{
		if (m_useTexturePtr != nullptr)
		{
			m_useTexturePtr->Release();
		}

		if (m_viewPtr != nullptr)
		{
			m_viewPtr->Release();
		}
	}

	ID3D11DepthStencilView * DepthStencilViewData::getViewPtr() const
	{
		return m_viewPtr;
	}
}