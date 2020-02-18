#include "TktkDirectX11Wrapper/Graphics/DepthStencil/Asset/DepthStencilData.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	DepthStencilData::DepthStencilData(const Vector2 & useTextureSize)
	{
		// �f�v�X�X�e���V���o�b�t�@�p�̃e�N�X�`���𐶐�
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

		// �f�v�X�E�X�e���V���o�b�t�@�r���[�̐���
		Screen::getDevicePtr()->CreateDepthStencilView(m_useTexturePtr, NULL, &m_viewPtr);
	}

	DepthStencilData::~DepthStencilData()
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

	ID3D11DepthStencilView * DepthStencilData::getViewPtr() const
	{
		return m_viewPtr;
	}
}