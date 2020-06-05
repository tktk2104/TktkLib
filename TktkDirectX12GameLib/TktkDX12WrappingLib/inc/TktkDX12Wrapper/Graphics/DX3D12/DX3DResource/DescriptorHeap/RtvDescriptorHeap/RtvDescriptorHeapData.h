#ifndef RTV_DESCRIPTOR_HEAP_DATA_H_
#define RTV_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include "RtvDescriptorHeapInitParam.h"

namespace tktk
{
	class RtvDescriptorHeapData
	{
	public:

		RtvDescriptorHeapData(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		~RtvDescriptorHeapData();

	public:

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		const std::vector<unsigned int>& getRenderTargetBufferIdArray() const;

		ID3D12DescriptorHeap* getPtr() const;

		void setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		void setRenderTarget(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

		void clearRenderTarget(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

	private:

		std::vector<unsigned int> m_renderTargetBufferIdArray{};

		ID3D12DescriptorHeap* m_descriptorHeap{ nullptr };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_DATA_H_