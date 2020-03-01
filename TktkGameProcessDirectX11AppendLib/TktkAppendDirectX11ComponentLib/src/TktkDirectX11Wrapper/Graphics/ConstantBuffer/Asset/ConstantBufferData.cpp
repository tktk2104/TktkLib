#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/ConstantBufferData.h"

namespace tktk
{
	ConstantBufferData::ConstantBufferData(SafetyVoidPtr && data)
		: m_bufferSize(data.getClassSize())
		, m_tempBufferPtr(std::move(data))
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = m_bufferSize + (m_bufferSize % 16U == 0U ? 0U : 16U - m_bufferSize % 16U); // バッファサイズは１６の倍数である必要があるため
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		Screen::getDevicePtr()->CreateBuffer(&bufferDesc, NULL, &m_bufferPtr);
	}

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

	void ConstantBufferData::addParamLocationImpl(int locationType, unsigned int locationFromBufferTop)
	{
		m_paramLocationMap.insert(std::make_pair(locationType, locationFromBufferTop));
	}
}