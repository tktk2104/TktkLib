#include "TktkDX12Wrapper/Graphics/DX3D12/VertexBuffer/VertexBuffer.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(unsigned int vertexBufferNum)
	{
		m_vertexBufferDataArray.resize(vertexBufferNum);
	}

	void VertexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_vertexBufferDataArray.at(id).set(commandList);
	}
}