#ifndef RTV_DESCRIPTOR_HEAP_H_
#define RTV_DESCRIPTOR_HEAP_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RtvDescriptorHeapData.h"

namespace tktk
{
	class RtvDescriptorHeap
	{
	public:

		RtvDescriptorHeap(unsigned int rtvDescriptorHeapNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		void setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
	
		void setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

	private:

		HeapArray<RtvDescriptorHeapData> m_rtvDescriptorHeapDataArray;
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_H_