#ifndef DESCRIPTOR_HEAP_DATA_H_
#define DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#include "DescriptorHeapInitParam.h"

namespace tktk
{
	class DescriptorHeapData
	{
	public:

		DescriptorHeapData() = default;
		~DescriptorHeapData();

	public:

		void initialize(ID3D12Device* device, const std::vector<DescriptorHeapInitParam>& initParamArray);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int descriptorHeapIndex);

		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		struct HeapHandleParam
		{
			unsigned int	m_numDescriptors;
			unsigned int	m_heapHandleIncrementSize;
		};

	private:

		std::vector<ID3D12DescriptorHeap*>	m_descriptorHeapArray{};
		std::vector<HeapHandleParam>		m_heapHandleParamArray{};
	};
}
#endif // !DESCRIPTOR_HEAP_DATA_H_