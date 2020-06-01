#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	ConstantBuffer::ConstantBuffer(unsigned int constantBufferNum)
		: m_constantBufferDataArray(constantBufferNum)
	{
	}

	void ConstantBuffer::create(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.emplaceAt(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::createConstantBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_constantBufferDataArray.at(id)->createConstantBufferView(device, heapHandle);
	}

	void ConstantBuffer::updateBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.at(id)->updateBuffer(device, constantBufferTypeSize, constantBufferDataTopPos);
	}
}