#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DX3DResource.h"

namespace tktk
{
	DX3DResource::DX3DResource(const DX3DResourceInitParam& initParam)
		: m_viewport(initParam.viewPortNum)
		, m_scissorRect(initParam.scissorRectNum)
		, m_graphicsPipeLine(initParam.pipeLineStateNum, initParam.rootSignatureNum)
		, m_descriptorHeap(initParam.descriptorHeapInitParam)
		, m_bufferResource(initParam.bufferResourceInitParam)
	{
	}

	void DX3DResource::createViewport(unsigned int id, const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewport.create(id, initParamArray);
	}

	void DX3DResource::createScissorRect(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRect.create(id, initParamArray);
	}

	void DX3DResource::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_graphicsPipeLine.createRootSignature(id, device, initParam);
	}

	void DX3DResource::createGraphicsPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_graphicsPipeLine.createPipeLineState(id, device, initParam, shaderFilePath);
	}

	void DX3DResource::createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_bufferResource.createVertexBuffer(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DResource::createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indices)
	{
		m_bufferResource.createIndexBuffer(id, device, indices);
	}

	void DX3DResource::createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.createConstantBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_bufferResource.createBackBuffer(id, swapChain, backBufferIndex);
	}

	void DX3DResource::createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize)
	{
		m_bufferResource.createDepthStencilBuffer(id, device, depthStencilSize);
	}

	void DX3DResource::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_descriptorHeap.createBasicDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuBasicHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case BasicDescriptorType::constantBuffer:

				m_bufferResource.createConstantBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;

			case BasicDescriptorType::textureBuffer:

				m_bufferResource.createShaderResourceView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_descriptorHeap.createRtvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuRtvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case RtvDescriptorType::normal:

				break;

			case RtvDescriptorType::backBuffer:

				m_bufferResource.createBackBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		m_descriptorHeap.createDsvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuDsvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case DsvDescriptorType::normal:

				m_bufferResource.createDepthStencilView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_bufferResource.gpuPriorityLoadTextureBuffer(id, device, commandList, formatParam, texDataPath);
	}

	void DX3DResource::updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.updateConstantBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_descriptorHeap.clearRenderTarget(id, device, commandList, rtvLocationIndex, color);
	}

	void DX3DResource::clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_descriptorHeap.clearDepthStencilViewAll(device, commandList);
	}

	const tktkMath::Vector3& DX3DResource::getTextureSize(unsigned int id) const
	{
		return m_bufferResource.getTextureSize(id);
	}

	void DX3DResource::setBackBufferRenderTarget(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int curBackBufferIndex)
	{
		m_descriptorHeap.setRenderTarget(0U, device, commandList, curBackBufferIndex, 1U);
	}

	void DX3DResource::setUseDepthStencilBackBufferRenderTarget(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int curBackBufferIndex)
	{
		m_descriptorHeap.setRenderTargetAndDepthStencil(0U, dsvDescriptorHeapId, device, commandList, curBackBufferIndex, 1U);
	}

	void DX3DResource::setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_viewport.set(id, commandList);
	}

	void DX3DResource::setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_scissorRect.set(id, commandList);
	}

	void DX3DResource::setGraphicsPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_graphicsPipeLine.set(id, commandList);
	}

	void DX3DResource::setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.setVertexBuffer(id, commandList);
	}

	void DX3DResource::setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.setIndexBuffer(id, commandList);
	}

	void DX3DResource::setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_descriptorHeap.set(device, commandList, heapParamArray);
	}

	void DX3DResource::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.useBackBuffer(id, commandList);
	}

	void DX3DResource::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.unUseBackBuffer(id, commandList);
	}
}