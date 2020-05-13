#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/DescriptorHeap.h"

namespace tktk
{
	DescriptorHeap::DescriptorHeap(int basicDescriptorHeapNum, int rtvDescriptorHeapNum, int dsvDescriptorHeapNum, int textureBufferNum, int constantBufferNum, int renderTargetBufferNum, int backBufferNum, int depthStencilBufferNum)
		: m_basicDescriptorHeap(basicDescriptorHeapNum)
		, m_rtvDescriptorHeap(rtvDescriptorHeapNum)
		, m_dsvDescriptorHeap(dsvDescriptorHeapNum)
		, m_textureBuffer(textureBufferNum)
		, m_constantBuffer(constantBufferNum)
		, m_renderTargetBuffer(renderTargetBufferNum, backBufferNum)
		, m_depthStencilBuffer(depthStencilBufferNum)
	{
	}

	void DescriptorHeap::set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		std::vector<ID3D12DescriptorHeap*> descriptorHeapArray{};
		descriptorHeapArray.reserve(heapParamArray.size());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				descriptorHeapArray.push_back(m_basicDescriptorHeap.getPtr(heapParam.m_id));
				break;
	
			case DescriptorHeapType::rtv:
	
				descriptorHeapArray.push_back(m_rtvDescriptorHeap.getPtr(heapParam.m_id));
				break;

			case DescriptorHeapType::dsv:

				descriptorHeapArray.push_back(m_dsvDescriptorHeap.getPtr(heapParam.m_id));
				break;
			}
		}
	
		commandList->SetDescriptorHeaps(descriptorHeapArray.size(), descriptorHeapArray.data());
	
		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:
	
				m_basicDescriptorHeap.setDescriptor(heapParam.m_id, device, commandList);
				break;
	
			case DescriptorHeapType::rtv:
	
				m_rtvDescriptorHeap.setDescriptor(heapParam.m_id, device, commandList);
				break;

			case DescriptorHeapType::dsv:

				m_dsvDescriptorHeap.setDescriptor(heapParam.m_id, device, commandList);
				break;
			}
		}
	}

	void DescriptorHeap::setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const
	{
		m_rtvDescriptorHeap.setRenderTarget(id, device, commandList, startRtvLocation, rtvCount, nullptr);
	}

	void DescriptorHeap::setRenderTargetAndDepthStencil(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount)
	{
		auto cpuHeapHandleArray = m_dsvDescriptorHeap.getCpuHeapHandleArray(depthStencilViewId, device);
		m_rtvDescriptorHeap.setRenderTarget(renderTargetId, device, commandList, startRtvLocation, rtvCount, cpuHeapHandleArray.data());
	}

	void DescriptorHeap::clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_rtvDescriptorHeap.clearRenderTarget(id, device, commandList, rtvLocationIndex, color);
	}

	void DescriptorHeap::clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_dsvDescriptorHeap.clearViewAll(device, commandList);
	}

	void DescriptorHeap::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_basicDescriptorHeap.create(id, device, initParam);
	
		auto cpuHeapHandleArray = m_basicDescriptorHeap.getCpuHeapHandleArray(id, device);
	
		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case BasicDescriptorType::constantBuffer:
	
				m_constantBuffer.createConstantBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
	
			case BasicDescriptorType::textureBuffer:
	
				m_textureBuffer.createShaderResourceView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DescriptorHeap::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeap.create(id, device, initParam);
	
		auto cpuHeapHandleArray = m_rtvDescriptorHeap.getCpuHeapHandleArray(id, device);
	
		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case RtvDescriptorType::normal:
	
				break;
	
			case RtvDescriptorType::backBuffer:
	
				m_renderTargetBuffer.createBackBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DescriptorHeap::createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dsvDescriptorHeap.create(id, device, initParam);

		auto cpuHeapHandleArray = m_dsvDescriptorHeap.getCpuHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case DsvDescriptorType::normal:

				m_depthStencilBuffer.createDepthStencilView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DescriptorHeap::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	void DescriptorHeap::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	void DescriptorHeap::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.cpuPriorityLoad(id, device, formatParam, texDataPath);
	}

	void DescriptorHeap::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.gpuPriorityLoad(id, device, commandList, formatParam, texDataPath);
	}

	const tktkMath::Vector3& DescriptorHeap::getTextureSize(unsigned int id) const
	{
		return m_textureBuffer.getTextureSize(id);
	}

	void DescriptorHeap::createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.create(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DescriptorHeap::updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBuffer.updateBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DescriptorHeap::createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_renderTargetBuffer.createBackBuffer(id, swapChain, backBufferIndex);
	}

	void DescriptorHeap::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.useBackBuffer(id, commandList);
	}

	void DescriptorHeap::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.unUseBackBuffer(id, commandList);
	}

	void DescriptorHeap::createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize)
	{
		m_depthStencilBuffer.create(id, device, depthStencilSize);
	}
}