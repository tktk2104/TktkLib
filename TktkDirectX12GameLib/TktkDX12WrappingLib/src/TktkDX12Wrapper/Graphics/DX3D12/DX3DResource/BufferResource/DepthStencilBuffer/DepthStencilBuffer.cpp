#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/DepthStencilBuffer/DepthStencilBuffer.h"

namespace tktk
{
	DepthStencilBuffer::DepthStencilBuffer(unsigned int depthStencilBufferNum)
		: m_depthStencilBufferDataArray(depthStencilBufferNum)
	{
	}

	void DepthStencilBuffer::create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize)
	{
		m_depthStencilBufferDataArray.emplaceAt(id, device, depthStencilSize);
	}

	void DepthStencilBuffer::createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_depthStencilBufferDataArray.at(id)->createDepthStencilView(device, heapHandle);
	}
}