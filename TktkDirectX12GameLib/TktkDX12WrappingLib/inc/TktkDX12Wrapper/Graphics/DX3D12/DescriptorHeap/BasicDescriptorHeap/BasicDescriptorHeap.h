#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <array>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	template <int BasicDescriptorHeapNum>
	class BasicDescriptorHeap
	{
	public:

		BasicDescriptorHeap() = default;

	public:

		void create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		void setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::array<BasicDescriptorHeapData, BasicDescriptorHeapNum> m_basicDescriptorHeapDataArray{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<int BasicDescriptorHeapNum>
	inline void BasicDescriptorHeap<BasicDescriptorHeapNum>::create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_basicDescriptorHeapDataArray.at(id).initialize(device, initParam);
	}

	template<int BasicDescriptorHeapNum>
	inline std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BasicDescriptorHeap<BasicDescriptorHeapNum>::getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const
	{
		return m_basicDescriptorHeapDataArray.at(id).getCpuHeapHandleArray(device);
	}

	template<int BasicDescriptorHeapNum>
	inline ID3D12DescriptorHeap* BasicDescriptorHeap<BasicDescriptorHeapNum>::getPtr(unsigned int id) const
	{
		return  m_basicDescriptorHeapDataArray.at(id).getPtr();
	}

	template<int BasicDescriptorHeapNum>
	inline void BasicDescriptorHeap<BasicDescriptorHeapNum>::setDescriptor(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const
	{
		m_basicDescriptorHeapDataArray.at(id).setDescriptor(device, commandList);
	}
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_