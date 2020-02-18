#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/VertexBuffer/VertexBuffer.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(const VertexBufferInitParams & params)
		: m_stride(params.stride)
		, m_offset(params.offset)
	{
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = params.bufferSize;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData{};
		subresourceData.pSysMem = params.bufferData;

		Screen::getDevicePtr()->CreateBuffer(&desc, &subresourceData, &m_vertexBufferPtr);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_vertexBufferPtr != nullptr)
		{
			m_vertexBufferPtr->Release();
		}
	}

	ID3D11Buffer * VertexBuffer::getVertexBufferPtr() const
	{
		return m_vertexBufferPtr;
	}

	unsigned int VertexBuffer::getStride() const
	{
		return m_stride;
	}

	unsigned int VertexBuffer::getOffset() const
	{
		return m_offset;
	}
}