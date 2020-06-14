#ifndef DSV_DESCRIPTOR_HEAP_DATA_H_
#define DSV_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include "DsvDescriptorHeapInitParam.h"

namespace tktk
{
	class DsvDescriptorHeapData
	{
	public:

		DsvDescriptorHeapData(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);
		~DsvDescriptorHeapData();

	public:

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		const std::vector<unsigned int>& getDepthStencilBufferIdArray() const;

		ID3D12DescriptorHeap* getPtr() const;

		void setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		void setOnlyDepthStencil(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		void clearView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	private:

		std::vector<unsigned int> m_depthStencilBufferIdArray{};

		ID3D12DescriptorHeap* m_descriptorHeap{ nullptr };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_DATA_H_