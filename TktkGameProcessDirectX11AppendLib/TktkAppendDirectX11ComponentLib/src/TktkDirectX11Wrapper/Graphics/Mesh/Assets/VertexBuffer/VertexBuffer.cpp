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

	void VertexBuffer::setBuffer() const
	{
		Screen::getDeviceContextPtr()->IASetVertexBuffers(
			0,
			1,
			&m_vertexBufferPtr,
			&m_stride,
			&m_offset
		);
	}
}