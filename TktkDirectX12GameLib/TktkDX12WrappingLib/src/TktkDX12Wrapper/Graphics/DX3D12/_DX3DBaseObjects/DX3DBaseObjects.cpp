#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <vector>

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(
		HWND hwnd,
		const tktkMath::Vector2& windowSize
	)
	{
		// デバイスを作る
		D3D12CreateDevice(
			nullptr,
			D3D_FEATURE_LEVEL_12_1,
			IID_PPV_ARGS(&m_device)
		);

		CreateDXGIFactory1(
			IID_PPV_ARGS(&m_factory)
		);

		// コマンドアロケータを作る
		m_device->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(&m_commandAllocator)
		);

		// コマンドリストを作る
		m_device->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			m_commandAllocator,
			nullptr,
			IID_PPV_ARGS(&m_commandList)
		);

		D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		// コマンドキューを作る
		m_device->CreateCommandQueue(
			&commandQueueDesc,
			IID_PPV_ARGS(&m_commandQueue)
		);

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = static_cast<unsigned int>(windowSize.x);
		swapChainDesc.Height = static_cast<unsigned int>(windowSize.y);
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// スワップチェーンを作る
		m_factory->CreateSwapChainForHwnd(
			m_commandQueue,
			hwnd,
			&swapChainDesc,
			nullptr,
			nullptr,
			&m_swapChain//static_cast<IDXGISwapChain1**>(&m_swapChain)
		);

		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 2;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		ID3D12DescriptorHeap* renderTargetViewHeaps{ nullptr };

		m_device->CreateDescriptorHeap(
			&heapDesc,
			IID_PPV_ARGS(&renderTargetViewHeaps)
		);

		std::vector<ID3D12Resource*> backBuffers(swapChainDesc.BufferCount);

		for (unsigned int i = 0; i < swapChainDesc.BufferCount; ++i)
		{
			m_swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffers.at(i)));

			D3D12_CPU_DESCRIPTOR_HANDLE handle = renderTargetViewHeaps->GetCPUDescriptorHandleForHeapStart();
			handle.ptr += i * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			m_device->CreateRenderTargetView(
				backBuffers.at(i),
				nullptr,
				handle
			);
		}

		m_commandAllocator->Reset();

		auto backBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();
		auto renderTargetViewHeap = renderTargetViewHeaps->GetCPUDescriptorHandleForHeapStart();
		renderTargetViewHeap.ptr += backBufferIndex * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		m_commandList->OMSetRenderTargets(1, &renderTargetViewHeap, true, nullptr);

		float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_commandList->ClearRenderTargetView(renderTargetViewHeap, clearColor, 0, nullptr);
		
		m_commandList->Close();

		ID3D12CommandList* commandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(1, commandLists);

		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		m_swapChain->Present(1, 0);
	}

	void DX3DBaseObjects::update()
	{
	}
}