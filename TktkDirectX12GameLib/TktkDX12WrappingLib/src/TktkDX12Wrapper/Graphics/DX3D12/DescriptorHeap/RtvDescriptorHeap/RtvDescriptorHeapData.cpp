#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/RtvDescriptorHeap/RtvDescriptorHeapData.h"

namespace tktk
{
	RtvDescriptorHeapData::~RtvDescriptorHeapData()
	{
		if (m_descriptorHeap != nullptr)
		{
			m_descriptorHeap->Release();
		}
	}

	void RtvDescriptorHeapData::initialize(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
		descHeapDesc.Flags = (initParam.m_shaderVisible) ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NodeMask = 0;
		descHeapDesc.NumDescriptors = initParam.m_descriptorParamArray.size();
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_descriptorHeap));
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeapData::getCpuHeapHandleArray(ID3D12Device* device) const
	{
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> handleArray;
		handleArray.reserve(m_descriptorHeap->GetDesc().NumDescriptors);

		auto cpuHandle = m_descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			handleArray.push_back(cpuHandle);
			cpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
		return handleArray;
	}

	ID3D12DescriptorHeap* RtvDescriptorHeapData::getPtr() const
	{
		return m_descriptorHeap;
	}

	void RtvDescriptorHeapData::setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		auto gpuHandle = m_descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < m_descriptorHeap->GetDesc().NumDescriptors; i++)
		{
			commandList->SetGraphicsRootDescriptorTable(i, gpuHandle);
			gpuHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		}
	}

	void RtvDescriptorHeapData::setRenderTarget(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		auto cpuHeapHandleArray = getCpuHeapHandleArray(device);
		commandList->OMSetRenderTargets(rtvCount, &cpuHeapHandleArray.at(startRtvLocationIndex), true, nullptr);
	}

	void RtvDescriptorHeapData::clearRenderTarget(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		auto cpuHeapHandleArray = getCpuHeapHandleArray(device);
		commandList->ClearRenderTargetView(cpuHeapHandleArray.at(rtvLocationIndex), (float*)&color, 0U, nullptr);
	}
}