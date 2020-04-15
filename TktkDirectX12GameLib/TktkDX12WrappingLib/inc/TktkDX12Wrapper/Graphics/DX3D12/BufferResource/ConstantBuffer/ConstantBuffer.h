#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <array>
#include "ConstantBufferData.h"

namespace tktk
{
	template <int ConstantBufferNum>
	class ConstantBuffer
	{
	public:

		ConstantBuffer() = default;

	public:

		template <class ConstantBufferDataType>
		void create(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);
	
		void createShaderResource(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
	
	private:

		std::array<ConstantBufferData, ConstantBufferNum> m_constantBufferDataArray{};
	};

	template<int ConstantBufferNum>
	template<class ConstantBufferDataType>
	inline void ConstantBuffer<ConstantBufferNum>::create(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		m_constantBufferDataArray.at(id).initialize<ConstantBufferDataType>(device, rawConstantBufferData);
	}

	template<int ConstantBufferNum>
	inline void ConstantBuffer<ConstantBufferNum>::createShaderResource(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_constantBufferDataArray.at(id).createShaderResource(device, heapHandle);
	}
}
#endif // !CONSTANT_BUFFER_H_