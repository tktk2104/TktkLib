#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DescriptorHeap/RtvDescriptorHeap/RtvDescriptorHeap.h"

namespace tktk
{
	RtvDescriptorHeap::RtvDescriptorHeap(unsigned int rtvDescriptorHeapNum)
		: m_rtvDescriptorHeapDataArray(rtvDescriptorHeapNum)
	{
	}

	void RtvDescriptorHeap::create(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeapDataArray.emplaceAt(id, device, initParam);
	}

	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeap::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeapDataArray.at(id)->getCpuHeapHandleArray(device);
	}

	ID3D12DescriptorHeap* RtvDescriptorHeap::getPtr(unsigned int id) const
	{
		return m_rtvDescriptorHeapDataArray.at(id)->getPtr();
	}

	void RtvDescriptorHeap::setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_rtvDescriptorHeapDataArray.at(id)->setDescriptor(device, commandList);
	}

	void RtvDescriptorHeap::setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const
	{
		m_rtvDescriptorHeapDataArray.at(id)->setRenderTarget(device, commandList, startRtvLocationIndex, rtvCount, useDsvHandle);
	}

	void RtvDescriptorHeap::clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_rtvDescriptorHeapDataArray.at(id)->clearRenderTarget(device, commandList, rtvLocationIndex, color);
	}
}