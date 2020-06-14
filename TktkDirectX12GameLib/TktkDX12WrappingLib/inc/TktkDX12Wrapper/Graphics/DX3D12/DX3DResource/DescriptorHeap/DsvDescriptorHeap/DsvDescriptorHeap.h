#ifndef DSV_DESCRIPTOR_HEAP_H_
#define DSV_DESCRIPTOR_HEAP_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DsvDescriptorHeapData.h"

namespace tktk
{
	class DsvDescriptorHeap
	{
	public:

		DsvDescriptorHeap(unsigned int dsvDescriptorHeapNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		const std::vector<unsigned int>& getDepthStencilBufferIdArray(unsigned int id) const;

		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		void setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		void setOnlyDepthStencil(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		void clearViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	private:

		HeapArray<DsvDescriptorHeapData> m_dsvDescriptorHeapDataArray;
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_H_