#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/Asset/ConstantBufferData.h"

namespace tktk
{
	ConstantBufferData::ConstantBufferData(SafetyVoidPtr && data)
		: m_bufferSize(data.getClassSize())
		, m_tempBufferPtr(std::move(data))
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = m_bufferSize + (m_bufferSize % 16U == 0U ? 0U : 16U - m_bufferSize % 16U); // �o�b�t�@�T�C�Y�͂P�U�̔{���ł���K�v�����邽��
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

	void ConstantBufferData::setBufferData(const SafetyVoidPtr & bufferData)
	{
		if (m_tempBufferPtr.getClassId() == bufferData.getClassId())
		{
			memcpy(m_tempBufferPtr.voidPtr(), bufferData.voidPtr(), bufferData.getClassSize());
			return;
		}
		throw std::runtime_error("getTempBufferPtr error BufferType Invalid type");
	}
}