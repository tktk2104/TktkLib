#include "TktkDirectX11Wrapper/Graphics/Mesh/Assets/IndexBuffer/IndexBuffer.h"

#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	IndexBuffer::IndexBuffer(const IndexBufferInitParams& params)
	{
		D3D11_BUFFER_DESC desc{};
		desc.ByteWidth = sizeof(unsigned int) * params.indices.size();
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData{};
		subresourceData.pSysMem = params.indices.data();

		Screen::getDevicePtr()->CreateBuffer(&desc, &subresourceData, &m_bufferPtr);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_bufferPtr != nullptr)
		{
			m_bufferPtr->Release();
		}
	}

	void IndexBuffer::setBuffer() const
	{
		Screen::getDeviceContextPtr()->IASetIndexBuffer(m_bufferPtr, DXGI_FORMAT_R32_UINT, 0);
	}
}