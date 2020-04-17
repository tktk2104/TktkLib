#include "TktkDX12Wrapper/Graphics/DX3D12/SwapChain/SwapChain.h"

namespace tktk
{
	SwapChain::~SwapChain()
	{
		if (m_swapChain != nullptr)
		{
			m_swapChain->Release();
		}
	}

	void SwapChain::initialize(HWND hwnd, IDXGIFactory6* factory, ID3D12CommandQueue* commandQueue, const tktkMath::Vector2& windowSize)
	{
		// �X���b�v�`�F�[�������
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = static_cast<unsigned int>(windowSize.x);
		swapChainDesc.Height = static_cast<unsigned int>(windowSize.y);
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapChainDesc.BufferCount = 2U;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		factory->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &m_swapChain);
	}

	IDXGISwapChain1* SwapChain::getPtr() const
	{
		return m_swapChain;
	}
}