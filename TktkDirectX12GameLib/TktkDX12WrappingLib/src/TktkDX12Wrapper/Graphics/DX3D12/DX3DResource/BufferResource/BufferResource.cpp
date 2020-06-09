#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/BufferResource.h"

namespace tktk
{
	BufferResource::BufferResource(const BufferResourceInitParam& initParam)
		: m_vertexBuffer(initParam.vertexBufferNum)
		, m_indexBuffer(initParam.indexBufferNum)
		, m_constantBuffer(initParam.constantBufferNum)
		, m_textureBuffer(initParam.textureBufferNum)
		, m_depthStencilBuffer(initParam.depthStencilBufferNum)
		, m_renderTargetBuffer(initParam.renderTargetBufferNum)
	{
	}

	void BufferResource::createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBuffer.create(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void BufferResource::setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_vertexBuffer.set(id, commandList);
	}

	void BufferResource::createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBuffer.create(id, device, indexDataArray);
	}

	void BufferResource::setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_indexBuffer.set(id, commandList);
	}

	void BufferResource::createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.create(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void BufferResource::createConstantBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_constantBuffer.createConstantBufferView(id, device, heapHandle);
	}

	void BufferResource::updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.updateBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void BufferResource::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	void BufferResource::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	void BufferResource::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath)
	{
		m_textureBuffer.cpuPriorityLoad(id, device, texDataPath);
	}

	void BufferResource::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		m_textureBuffer.gpuPriorityLoad(id, device, commandList, texDataPath);
	}

	void BufferResource::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_textureBuffer.createShaderResourceView(id, device, heapHandle);
	}

	const tktkMath::Vector3& BufferResource::getTextureSize(unsigned int id) const
	{
		return m_textureBuffer.getTextureSize(id);
	}

	void BufferResource::createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize)
	{
		m_depthStencilBuffer.create(id, device, depthStencilSize);
	}

	void BufferResource::createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_depthStencilBuffer.createDepthStencilView(id, device, heapHandle);
	}

	void BufferResource::createRenderTargetBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_renderTargetBuffer.create(id, device, renderTargetSize, clearColor);
	}

	void BufferResource::createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_renderTargetBuffer.create(id, swapChain, backBufferIndex);
	}

	void BufferResource::createRenderTargetView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_renderTargetBuffer.createRenderTargetView(id, device, heapHandle);
	}

	void BufferResource::createRtvShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_renderTargetBuffer.createShaderResourceView(id, device, heapHandle);
	}

	void BufferResource::useAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.useAsRenderTargetBuffer(id, commandList);
	}

	void BufferResource::unUseAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.unUseAsRenderTargetBuffer(id, commandList);
	}

	void BufferResource::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.useAsBackBuffer(id, commandList);
	}

	void BufferResource::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.unUseAsBackBuffer(id, commandList);
	}
}