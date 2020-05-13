#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/DepthStencilBuffer/DepthStencilBufferData.h"

namespace tktk
{
	DepthStencilBufferData::DepthStencilBufferData(ID3D12Device* device, const tktkMath::Vector2 & depthStencilSize)
	{
		D3D12_RESOURCE_DESC depthStencilResDesc{};
		depthStencilResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depthStencilResDesc.Width = static_cast<unsigned int>(depthStencilSize.x);
		depthStencilResDesc.Height = static_cast<unsigned int>(depthStencilSize.y);
		depthStencilResDesc.DepthOrArraySize = 1;
		depthStencilResDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilResDesc.SampleDesc.Count = 1;
		depthStencilResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_HEAP_PROPERTIES depthHeapProp{};
		depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
		depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_CLEAR_VALUE depthClearValue{};
		depthClearValue.DepthStencil.Depth = 1.0f;
		depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

		device->CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthStencilResDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthClearValue,
			IID_PPV_ARGS(&m_depthStencilBuffer)
		);
	}

	void DepthStencilBufferData::createDepthStencilView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		device->CreateDepthStencilView(
			m_depthStencilBuffer,
			&dsvDesc,
			heapHandle
		);
	}
}