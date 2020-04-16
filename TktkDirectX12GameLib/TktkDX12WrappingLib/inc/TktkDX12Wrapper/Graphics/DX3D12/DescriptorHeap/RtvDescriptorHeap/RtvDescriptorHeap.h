#ifndef RTV_DESCRIPTOR_HEAP_H_
#define RTV_DESCRIPTOR_HEAP_H_

#include <array>
#include "RtvDescriptorHeapData.h"

namespace tktk
{
	template <int RtvDescriptorHeapNum>
	class RtvDescriptorHeap
	{
	public:

		RtvDescriptorHeap() = default;

	public:

		void create(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		void setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
	
		void setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

	private:

		std::array<RtvDescriptorHeapData, RtvDescriptorHeapNum> m_rtvDescriptorHeapDataArray{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<int RtvDescriptorHeapNum>
	inline void RtvDescriptorHeap<RtvDescriptorHeapNum>::create(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeapDataArray.at(id).initialize(device, initParam);
	}

	template<int RtvDescriptorHeapNum>
	inline std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> RtvDescriptorHeap<RtvDescriptorHeapNum>::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_rtvDescriptorHeapDataArray.at(id).getCpuHeapHandleArray(device);
	}

	template<int RtvDescriptorHeapNum>
	inline ID3D12DescriptorHeap* RtvDescriptorHeap<RtvDescriptorHeapNum>::getPtr(unsigned int id) const
	{
		return m_rtvDescriptorHeapDataArray.at(id).getPtr();
	}

	template<int RtvDescriptorHeapNum>
	inline void RtvDescriptorHeap<RtvDescriptorHeapNum>::setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_rtvDescriptorHeapDataArray.at(id).setDescriptor(device, commandList);
	}

	template<int RtvDescriptorHeapNum>
	inline void RtvDescriptorHeap<RtvDescriptorHeapNum>::setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const
	{
		m_rtvDescriptorHeapDataArray.at(id).setRenderTarget(device, commandList, startRtvLocationIndex, rtvCount);
	}

	template<int RtvDescriptorHeapNum>
	inline void RtvDescriptorHeap<RtvDescriptorHeapNum>::clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_rtvDescriptorHeapDataArray.at(id).clearRenderTarget(device, commandList, rtvLocationIndex, color);
	}
}
#endif // !RTV_DESCRIPTOR_HEAP_H_