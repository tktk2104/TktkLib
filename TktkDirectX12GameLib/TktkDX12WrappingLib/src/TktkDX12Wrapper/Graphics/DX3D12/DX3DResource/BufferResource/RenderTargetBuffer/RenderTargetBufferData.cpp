#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/RenderTargetBuffer/RenderTargetBufferData.h"

namespace tktk
{
	RenderTargetBufferData::~RenderTargetBufferData()
	{
		if (m_mustRelease && m_renderTargetBuffer != nullptr)
		{
			m_renderTargetBuffer->Release();
		}
	}

	void RenderTargetBufferData::initializeBackBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_mustRelease = false;
		swapChain->GetBuffer(backBufferIndex, IID_PPV_ARGS(&m_renderTargetBuffer));
	}

	D3D12_RESOURCE_BARRIER RenderTargetBufferData::createBarrierDesc(D3D12_RESOURCE_STATES beforState, D3D12_RESOURCE_STATES afterState) const
	{
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_renderTargetBuffer;
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = beforState;
		barrierDesc.Transition.StateAfter = afterState;
		return barrierDesc;
	}

	void RenderTargetBufferData::createRenderTargetView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		device->CreateRenderTargetView(m_renderTargetBuffer, nullptr, heapHandle);
	}
}