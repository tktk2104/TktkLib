#include "TktkDX12Wrapper/Graphics/DX3D12/VertexBuffer/VertexBuffer.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(unsigned int vertexBufferNum)
	{
		m_vertexBufferDataArray.resize(vertexBufferNum);
	}

	void VertexBuffer::create(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBufferDataArray.at(id).initialize(device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void VertexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_vertexBufferDataArray.at(id).set(commandList);
	}
}