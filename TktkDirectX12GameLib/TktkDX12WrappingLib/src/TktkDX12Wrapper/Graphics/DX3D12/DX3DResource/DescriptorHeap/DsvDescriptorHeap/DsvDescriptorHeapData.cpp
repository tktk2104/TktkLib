#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/DsvDescriptorHeap/DsvDescriptorHeapData.h"

namespace tktk
{
	DsvDescriptorHeapData::DsvDescriptorHeapData(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Flags = (initParam.shaderVisible) ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = initParam.descriptorParamArray.size();
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap));

		m_depthStencilBufferIdArray.reserve(descHeapDesc.NumDescriptors);

		for (const auto& node : initParam.descriptorParamArray)
		{
			m_depthStencilBufferIdArray.push_back(node.id);
		}
	}

	DsvDescriptorHeapData::~DsvDescriptorHeapData()
	{
		if (m_descriptorHeap != nullptr)
		{
			m_descriptorHeap->Release();
		}
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DsvDescriptorHeapData::getCpuHeapHandleArray(ID3D12Device* device) const
	{
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		handleArray.reserve(m_descriptorHeap->GetDesc().NumDescriptors);

		auto cpuHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		}
		return handleArray;
	}

	const std::vector<unsigned int>& DsvDescriptorHeapData::getDepthStencilBufferIdArray() const
	{
		return m_depthStencilBufferIdArray;
	}

	ID3D12DescriptorHeap* DsvDescriptorHeapData::getPtr() const
	{
		return m_descriptorHeap;
	}

	void DsvDescriptorHeapData::setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		auto gpuHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			commandList->SetGraphicsRootDescriptorTable(i, gpuHandle);
			gpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
		}
	}

	void DsvDescriptorHeapData::setOnlyDepthStencil(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		commandList->OMSetRenderTargets(0, nullptr, true, getCpuHeapHandleArray(device).data());
	}

	void DsvDescriptorHeapData::clearView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		for (const auto& node : getCpuHeapHandleArray(device))
		{
			commandList->ClearDepthStencilView(node, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		}
	}
}