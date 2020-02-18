#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/ConstantBufferData.h"

namespace tktk
{
	ConstantBufferData::~ConstantBufferData()
	{
		if (m_bufferPtr != nullptr)
		{
			m_bufferPtr->Release();
		}
	}

	void ConstantBufferData::updateBuffer()
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubresource{};
		Screen::getDeviceContextPtr()->Map(m_bufferPtr, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
		memcpy_s(mappedSubresource.pData, mappedSubresource.RowPitch, m_tempBufferPtr.voidPtr(), m_bufferSize);
		Screen::getDeviceContextPtr()->Unmap(m_bufferPtr, 0);
	}

	ID3D11Buffer * ConstantBufferData::getBufferPtr() const
	{
		return m_bufferPtr;
	}

	void ConstantBufferData::addParamLocation(int locationType, unsigned int locationFromBufferTop)
	{
		m_paramLocationMap.insert(std::make_pair(locationType, locationFromBufferTop));
	}
}