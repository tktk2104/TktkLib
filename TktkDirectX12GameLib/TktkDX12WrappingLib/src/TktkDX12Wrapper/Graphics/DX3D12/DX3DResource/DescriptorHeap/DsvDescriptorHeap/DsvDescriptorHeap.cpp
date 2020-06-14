#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/DsvDescriptorHeap/DsvDescriptorHeap.h"

namespace tktk
{
	DsvDescriptorHeap::DsvDescriptorHeap(unsigned int dsvDescriptorHeapNum)
		: m_dsvDescriptorHeapDataArray(dsvDescriptorHeapNum)
	{
	}

	void DsvDescriptorHeap::create(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dsvDescriptorHeapDataArray.emplaceAt(id, device,initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> DsvDescriptorHeap::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getCpuHeapHandleArray(device);
	}

	const std::vector<unsigned int>& DsvDescriptorHeap::getDepthStencilBufferIdArray(unsigned int id) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getDepthStencilBufferIdArray();
	}

	ID3D12DescriptorHeap* DsvDescriptorHeap::getPtr(unsigned int id) const
	{
		return m_dsvDescriptorHeapDataArray.at(id)->getPtr();
	}

	void DsvDescriptorHeap::setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_dsvDescriptorHeapDataArray.at(id)->setDescriptor(device, commandList);
	}

	void DsvDescriptorHeap::setOnlyDepthStencil(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_dsvDescriptorHeapDataArray.at(id)->setOnlyDepthStencil(device, commandList);
	}

	void DsvDescriptorHeap::clearViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		for (unsigned int i = 0; i < m_dsvDescriptorHeapDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_dsvDescriptorHeapDataArray.at(i);

			if (ptr != nullptr) ptr->clearView(device, commandList);
		}
	}
}