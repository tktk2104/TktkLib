#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/RenderTargetBuffer/RenderTargetBuffer.h"

namespace tktk
{
	RenderTargetBuffer::RenderTargetBuffer(unsigned int renderTargetBufferNum, unsigned int backBufferNum)
	{
		m_renderTargetBufferDataArray.resize(renderTargetBufferNum);
		m_backBufferDataArray.resize(backBufferNum);
	}

	void RenderTargetBuffer::createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_backBufferDataArray.at(id).initializeBackBuffer(swapChain, backBufferIndex);
	}

	void RenderTargetBuffer::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_backBufferDataArray.at(id).createBarrierDesc(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_backBufferDataArray.at(id).createBarrierDesc(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::createBackBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_backBufferDataArray.at(id).createRenderTargetView(device, heapHandle);
	}
}