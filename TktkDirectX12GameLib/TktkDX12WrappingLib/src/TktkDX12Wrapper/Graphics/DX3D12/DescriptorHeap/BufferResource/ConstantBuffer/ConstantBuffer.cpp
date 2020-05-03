#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	ConstantBuffer::ConstantBuffer(unsigned int constantBufferNum)
	{
		m_constantBufferDataArray.resize(constantBufferNum);
	}

	void ConstantBuffer::create(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.at(id).initialize(device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::createConstantBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_constantBufferDataArray.at(id).createConstantBufferView(device, heapHandle);
	}

	void ConstantBuffer::updateBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.at(id).updateBuffer(device, constantBufferTypeSize, constantBufferDataTopPos);
	}
}