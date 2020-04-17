#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <vector>
#include "ConstantBufferData.h"

namespace tktk
{
	class ConstantBuffer
	{
	public:

		ConstantBuffer(unsigned int constantBufferNum);

	public:

		void create(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		template <class ConstantBufferDataType>
		void create(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);
	
		void createConstantBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
	
	private:

		std::vector<ConstantBufferData> m_constantBufferDataArray{};
	};
	//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//┃ここから下は関数の実装
	//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ConstantBufferDataType>
	inline void ConstantBuffer::create(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		m_constantBufferDataArray.at(id).initialize<ConstantBufferDataType>(device, rawConstantBufferData);
	}
}
#endif // !CONSTANT_BUFFER_H_