#include "TktkDX12Wrapper/Graphics/DX3D12/IndexBuffer/IndexBuffer.h"

namespace tktk
{
	IndexBuffer::IndexBuffer(unsigned int indexBufferNum)
	{
		m_indexBufferDataArray.resize(indexBufferNum);
	}

	void IndexBuffer::create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBufferDataArray.at(id).initialize(device, indexDataArray);
	}

	void IndexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_indexBufferDataArray.at(id).set(commandList);
	}
}