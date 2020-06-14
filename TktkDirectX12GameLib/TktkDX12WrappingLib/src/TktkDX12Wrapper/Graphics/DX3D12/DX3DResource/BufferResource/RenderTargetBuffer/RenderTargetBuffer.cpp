#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/RenderTargetBuffer/RenderTargetBuffer.h"

namespace tktk
{
	RenderTargetBuffer::RenderTargetBuffer(unsigned int renderTargetBufferNum)
		: m_renderTargetBufferDataArray(renderTargetBufferNum)
	{
	}

	void RenderTargetBuffer::create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_renderTargetBufferDataArray.emplaceAt(id, device, renderTargetSize, clearColor);
	}

	void RenderTargetBuffer::create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_renderTargetBufferDataArray.emplaceAt(id, swapChain, backBufferIndex);
	}

	void RenderTargetBuffer::useAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_renderTargetBufferDataArray.at(id)->createBarrierDesc(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::unUseAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_renderTargetBufferDataArray.at(id)->createBarrierDesc(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::useAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_renderTargetBufferDataArray.at(id)->createBarrierDesc(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::unUseAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_renderTargetBufferDataArray.at(id)->createBarrierDesc(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBuffer::createRenderTargetView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_renderTargetBufferDataArray.at(id)->createRenderTargetView(device, heapHandle);
	}

	void RenderTargetBuffer::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_renderTargetBufferDataArray.at(id)->createShaderResourceView(device, heapHandle);
	}

	const tktkMath::Vector2& RenderTargetBuffer::getRenderTargetSize(unsigned int id) const
	{
		return m_renderTargetBufferDataArray.at(id)->getRenderTargetSize();
	}
}