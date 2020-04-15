#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/DescriptorHeapData.h"

namespace tktk
{
	DescriptorHeapData::~DescriptorHeapData()
	{
		for (auto descriptorHeap : m_descriptorHeapArray)
		{
			if (descriptorHeap != nullptr)
			{
				descriptorHeap->Release();
			}
		}
	}

	void DescriptorHeapData::initialize(ID3D12Device* device, const std::vector<DescriptorHeapInitParam>& initParamArray)
	{
		m_descriptorHeapArray.clear();
		m_descriptorHeapArray.reserve(initParamArray.size());

		m_heapHandleParamArray.clear();
		m_heapHandleParamArray.reserve(initParamArray.size());

		for (const auto& initParam : initParamArray)
		{
			ID3D12DescriptorHeap* descriptorHeap{ nullptr };

			D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
			descHeapDesc.Flags = initParam.m_flag;
			descHeapDesc.NodeMask = 0;
			descHeapDesc.NumDescriptors = initParam.m_descriptorParamArray.size();
			descHeapDesc.Type = initParam.m_type;
			device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descriptorHeap));

			m_descriptorHeapArray.push_back(descriptorHeap);
			m_heapHandleParamArray.push_back({ initParam.m_descriptorParamArray.size(), device->GetDescriptorHandleIncrementSize(initParam.m_type) });
		}
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DescriptorHeapData::getCpuHeapHandleArray(unsigned int descriptorHeapIndex)
	{
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		handleArray.reserve(m_heapHandleParamArray.at(descriptorHeapIndex).m_numDescriptors);

		auto cpuHandle = m_descriptorHeapArray.at(descriptorHeapIndex)->GetCPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_heapHandleParamArray.at(descriptorHeapIndex).m_numDescriptors; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += m_heapHandleParamArray.at(descriptorHeapIndex).m_heapHandleIncrementSize;
		}
		return handleArray;
	}

	void DescriptorHeapData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->SetDescriptorHeaps(m_descriptorHeapArray.size(), m_descriptorHeapArray.data());

		for (unsigned int i = 0; i < m_descriptorHeapArray.size(); i++)
		{
			auto gpuHandle = m_descriptorHeapArray.at(i)->GetGPUDescriptorHandleForHeapStart();

			for (unsigned int j = 0; j < m_heapHandleParamArray.at(i).m_numDescriptors; j++)
			{
				commandList->SetGraphicsRootDescriptorTable(j, gpuHandle);
				gpuHandle.ptr += m_heapHandleParamArray.at(i).m_heapHandleIncrementSize;
			}
		}
	}
}