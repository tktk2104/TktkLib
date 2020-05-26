#ifndef BASIC_DESCRIPTOR_HEAP_DATA_H_
#define BASIC_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#include "BasicDescriptorHeapInitParam.h"

namespace tktk
{
	class BasicDescriptorHeapData
	{
	public:

		BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		~BasicDescriptorHeapData();

	public:

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr() const;

		void setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public:

		ID3D12DescriptorHeap*	m_descriptorHeap{ nullptr };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_DATA_H_