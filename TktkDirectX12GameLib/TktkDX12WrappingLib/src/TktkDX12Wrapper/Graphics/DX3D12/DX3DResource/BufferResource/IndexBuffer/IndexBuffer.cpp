#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/IndexBuffer/IndexBuffer.h"

namespace tktk
{
	IndexBuffer::IndexBuffer(unsigned int indexBufferNum)
		: m_indexBufferDataArray(indexBufferNum)
	{
	}

	void IndexBuffer::create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBufferDataArray.emplaceAt(id, device, indexDataArray);
	}

	void IndexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_indexBufferDataArray.at(id)->set(commandList);
	}
}