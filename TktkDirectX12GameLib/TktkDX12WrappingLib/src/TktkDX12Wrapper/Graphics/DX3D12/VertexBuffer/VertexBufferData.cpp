#include "TktkDX12Wrapper/Graphics/DX3D12/VertexBuffer/VertexBufferData.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	VertexBufferData::~VertexBufferData()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
		}
	}

	void VertexBufferData::set(ID3D12GraphicsCommandList* commandList)
	{
#ifdef _DEBUG
		if (m_vertexBuffer == nullptr)
		{
			throw std::runtime_error("Not Create VertexBuffer");
		}
#endif // _DEBUG
		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	}

	void VertexBufferData::createVertexBuffer(ID3D12Device* device, unsigned int resouseWidth)
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
		}

		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = (UINT64)resouseWidth;
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)
		);
	}

	void VertexBufferData::createVertexBufferView(unsigned int bufferSizeInByte, unsigned int bufferStrideInBytes)
	{
		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = bufferSizeInByte;
		m_vertexBufferView.StrideInBytes = bufferStrideInBytes;
	}
}