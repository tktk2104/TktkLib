#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	class BasicDescriptorHeap
	{
	public:

		BasicDescriptorHeap(unsigned int basicDescriptorHeapNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		void setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<BasicDescriptorHeapData> m_basicDescriptorHeapDataArray;
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_