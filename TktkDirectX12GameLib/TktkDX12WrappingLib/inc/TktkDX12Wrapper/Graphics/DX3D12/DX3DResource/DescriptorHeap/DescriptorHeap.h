#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include "DescriptorHeapInitParam.h"
#include "DescriptorHeapParam.h"

#include "BasicDescriptorHeap/BasicDescriptorHeap.h"
#include "RtvDescriptorHeap/RtvDescriptorHeap.h"
#include "DsvDescriptorHeap/DsvDescriptorHeap.h"

namespace tktk
{
	class DescriptorHeap
	{
	public:

		DescriptorHeap(const DescriptorHeapInitParam& initParam);

	public:

		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

		void setRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;
		void setRenderTargetAndDepthStencil(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount);
		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		void clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuBasicHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuRtvHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuDsvHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	private:

		BasicDescriptorHeap	m_basicDescriptorHeap;
		RtvDescriptorHeap	m_rtvDescriptorHeap;
		DsvDescriptorHeap	m_dsvDescriptorHeap;
	};
}
#endif // !DESCRIPTOR_HEAP_H_