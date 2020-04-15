#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <d3d12.h>

namespace tktk
{
	class ConstantBufferData
	{
	public:

		ConstantBufferData() = default;
		~ConstantBufferData();

	public:

		template <class ConstantBufferDataType>
		void initialize(ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);

		void createShaderResource(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		void createBuffer(ID3D12Device* device, unsigned int bufferSize);


	private:

		ID3D12Resource* m_constantBuffer{ nullptr };
	};

	template<class ConstantBufferDataType>
	inline void ConstantBufferData::initialize(ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		if (m_constantBuffer != nullptr)
		{
			m_constantBuffer->Release();
		}

		createBuffer(device, sizeof(ConstantBufferDataType));

		ConstantBufferDataType* mappedBuffer{ nullptr };
		m_constantBuffer->Map(0, nullptr, (void**)&mappedBuffer);
		*mappedBuffer = rawConstantBufferData;
		m_constantBuffer->Unmap(0, nullptr);
	}
}
#endif // !CONSTANT_BUFFER_DATA_H_