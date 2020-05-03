#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/ConstantBuffer/ConstantBufferData.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	ConstantBufferData::~ConstantBufferData()
	{
		if (m_constantBuffer != nullptr)
		{
			m_constantBuffer->Release();
		}
	}

	void ConstantBufferData::initialize(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		createBuffer(device, constantBufferTypeSize);

		void* mappedBuffer{ nullptr };
		m_constantBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, constantBufferDataTopPos, constantBufferTypeSize);
		m_constantBuffer->Unmap(0, nullptr);
	}

	void ConstantBufferData::createConstantBufferView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
#ifdef _DEBUG
		if (m_constantBuffer == nullptr)
		{
			throw std::runtime_error("Not Create ConstantBuffer");
		}
#endif // _DEBUG

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
		cbvDesc.BufferLocation = m_constantBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = static_cast<UINT>(m_constantBuffer->GetDesc().Width);

		device->CreateConstantBufferView(&cbvDesc, heapHandle);
	}

	void ConstantBufferData::updateBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
#ifdef _DEBUG
		if (m_constantBuffer == nullptr)
		{
			throw std::runtime_error("Not Create ConstantBuffer");
		}
#endif // _DEBUG

		void* mappedBuffer{ nullptr };
		m_constantBuffer->Map(0, nullptr, &mappedBuffer);
		memcpy(mappedBuffer, constantBufferDataTopPos, constantBufferTypeSize);
		m_constantBuffer->Unmap(0, nullptr);
	}

	void ConstantBufferData::createBuffer(ID3D12Device* device, unsigned int bufferSize)
	{
		if (m_constantBuffer != nullptr)
		{
			m_constantBuffer->Release();
		}

		D3D12_HEAP_PROPERTIES constBuffHeapProp{};
		constBuffHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		constBuffHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		constBuffHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		constBuffHeapProp.CreationNodeMask = 0;
		constBuffHeapProp.VisibleNodeMask = 0;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format = DXGI_FORMAT_UNKNOWN;
		resDesc.Width = (bufferSize + 0xff) & ~0xff;
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.SampleDesc.Quality = 0;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&constBuffHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_constantBuffer)
		);
	}
}