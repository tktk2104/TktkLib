#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor)
		: m_viewport(initParam.viewPortNum)
		, m_scissorRect(initParam.scissorRectNum)
		, m_vertexBuffer(initParam.vertexBufferNum)
		, m_indexBuffer(initParam.indexBufferNum)
		, m_graphicsPipeLineState(initParam.graphicsPipeLineNum, initParam.rootSignatureNum)
		, m_descriptorHeap(initParam.basicDescriptorHeapNum, initParam.rtvDescriptorHeapNum, initParam.dsvDescriptorHeapNum, initParam.textureBufferNum, initParam.constantBufferNum, initParam.renderTargetBufferNum, initParam.backBufferNum, initParam.depthStencilBufferNum)
		, m_backGroundColor(backGroundColor)
	{
#ifdef _DEBUG
		{
			ID3D12Debug* debugLayer{ nullptr };
			D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
			debugLayer->EnableDebugLayer();

			ID3D12Debug1* debugLayer1{ nullptr };
			debugLayer->QueryInterface(IID_PPV_ARGS(&debugLayer1));
			debugLayer1->SetEnableGPUBasedValidation(true);

			debugLayer1->Release();
			debugLayer->Release();
		}
#endif // _DEBUG

		// デバイスを作る
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));

		// ファクトリを作る
#ifdef _DEBUG
		CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
#else
		CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#endif

		// コマンドアロケータを作る
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

		// コマンドリストを作る
		m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

		// コマンドキューを作る
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		
		// スワップチェーンを作る
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = static_cast<unsigned int>(windowSize.x);
		swapChainDesc.Height = static_cast<unsigned int>(windowSize.y);
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
		swapChainDesc.BufferCount = 2U;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		m_factory->CreateSwapChainForHwnd(m_commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &m_swapChain);

		// フェンスを初期化する
		m_fence.initialize(m_device);

		// 初回リセット
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// ビューポートを作る
		m_viewport.create(0, { { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// シザー矩形を作る
		m_scissorRect.create(0, { { tktkMath::vec2Zero, windowSize } });

		// スワップチェーンのバックバッファーをディスクリプタヒープで使うための準備
		for (unsigned int i = 0; i < 2U; ++i)
		{
			m_descriptorHeap.createBackBuffer(i, m_swapChain, i);
		}

		// バックバッファー用のディスクリプタヒープを作る
		{
			RtvDescriptorHeapInitParam initParam{};
			initParam.m_shaderVisible = false;
			initParam.m_descriptorParamArray.resize(2U);
			initParam.m_descriptorParamArray.at(0U).m_type = RtvDescriptorType::backBuffer;
			initParam.m_descriptorParamArray.at(0U).m_id = 0U;
			initParam.m_descriptorParamArray.at(1U).m_type = RtvDescriptorType::backBuffer;
			initParam.m_descriptorParamArray.at(1U).m_id = 1U;

			m_descriptorHeap.createRtvDescriptorHeap(0U, m_device, initParam);
		}

		// デフォルトの深度バッファーと深度ディスクリプタヒープを作るを作る
		{
			m_descriptorHeap.createDepthStencilBuffer(0U, m_device, windowSize);

			DsvDescriptorHeapInitParam initParam{};
			initParam.m_shaderVisible = false;
			initParam.m_descriptorParamArray.push_back({ DsvDescriptorType::normal, 0U });

			m_descriptorHeap.createDsvDescriptorHeap(0U, m_device, initParam);
		}
	}

	DX3DBaseObjects::~DX3DBaseObjects()
	{
		if (m_device != nullptr)
		{
			m_device->Release();
		}
		if (m_factory != nullptr)
		{
			m_factory->Release();
		}
		if (m_commandAllocator != nullptr)
		{
			m_commandAllocator->Release();
		}
		if (m_commandList != nullptr)
		{
			m_commandList->Release();
		}
		if (m_commandQueue != nullptr)
		{
			m_commandQueue->Release();
		}
		if (m_swapChain != nullptr)
		{
			m_swapChain->Release();
		}
	}

	void DX3DBaseObjects::beginDraw()
	{
		// 現在のバックバッファーのインデックスを取得する
		m_curBackBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();

		// バックバッファをレンダーターゲット状態にする
		m_descriptorHeap.useBackBuffer(m_curBackBufferIndex, m_commandList);

		// 現在のバックバッファーを描画先に設定する
		setBackBufferRenderTarget();

		// 現在のバックバッファーを指定した単色で塗りつぶす
		m_descriptorHeap.clearRenderTarget(0U, m_device, m_commandList, m_curBackBufferIndex, m_backGroundColor);
		
		// 全てのデプスステンシルビューをクリアする
		m_descriptorHeap.clearDepthStencilViewAll(m_device, m_commandList);

		// ビューポートを設定する
		m_viewport.set(0, m_commandList);
		
		// シザー矩形を設定する
		m_scissorRect.set(0, m_commandList);

		//// グラフィックパイプラインステートを設定する
		//m_graphicsPipeLineState.set(0U, m_commandList);
		//
		// グラフィックパイプラインにディスクリプタヒープを設定する
		//m_descriptorHeap.set(m_device, m_commandList, { { DescriptorHeapType::basic, 0U } });
		//
		//// トライアングルリストで描画するように設定する
		//m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//
		//// 頂点バッファ情報を設定する
		//m_vertexBuffer.set(0, m_commandList);
		//
		//// インデックスバッファ情報を設定する
		//m_indexBuffer.set(0, m_commandList);
		//
		//// 描画
		//m_commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}

	void DX3DBaseObjects::endDraw()
	{
		// バックバッファをプリセット状態にする
		m_descriptorHeap.unUseBackBuffer(m_curBackBufferIndex, m_commandList);

		executeCommandList();

		// 画面をフリップする
		m_swapChain->Present(1, 0);
	}

	void DX3DBaseObjects::executeCommandList()
	{
		// コマンドリストを閉じる
		m_commandList->Close();

		// コマンドリストを実行する
		ID3D12CommandList* commandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(1, commandLists);

		// GPU処理が終わるまで待つ
		m_fence.waitGpuProcess(m_commandQueue);

		// コマンドアロケータをリセットする
		m_commandAllocator->Reset();

		// コマンドリストをリセットする
		m_commandList->Reset(m_commandAllocator, nullptr);
	}

	void DX3DBaseObjects::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_graphicsPipeLineState.createRootSignature(id, m_device, initParam);
	}

	void DX3DBaseObjects::createGraphicsPipeLineState(unsigned int graphicsPipeLineId, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId)
	{
		m_graphicsPipeLineState.createGraphicsPipeLineState(graphicsPipeLineId, m_device, initParam, shaderFilePath, useRootSignatureId);
	}

	void DX3DBaseObjects::createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBuffer.create(id, m_device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_indexBuffer.create(id, m_device, indices);
	}

	void DX3DBaseObjects::createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_descriptorHeap.createConstantBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize)
	{
		m_descriptorHeap.createDepthStencilBuffer(id, m_device, depthStencilSize);
	}

	void DX3DBaseObjects::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_descriptorHeap.createBasicDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_descriptorHeap.createDsvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_descriptorHeap.gpuPriorityLoadTextureBuffer(id, m_device, m_commandList, formatParam, texDataPath);
	}

	void DX3DBaseObjects::updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_descriptorHeap.updateConstantBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureSize(unsigned int id) const
	{
		return m_descriptorHeap.getTextureSize(id);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::setBackBufferRenderTarget()
	{
		m_descriptorHeap.setRenderTarget(0U, m_device, m_commandList, m_curBackBufferIndex, 1U);
	}

	void DX3DBaseObjects::setUseDepthStencilBackBufferRenderTarget(unsigned int depthStencilViewId)
	{
		m_descriptorHeap.setRenderTargetAndDepthStencil(0U, depthStencilViewId, m_device, m_commandList, m_curBackBufferIndex, 1U);
	}

	void DX3DBaseObjects::setViewport(unsigned int id)
	{
		m_viewport.set(id, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(unsigned int id)
	{
		m_scissorRect.set(id, m_commandList);
	}

	void DX3DBaseObjects::setGraphicsPipeLineState(unsigned int id)
	{
		m_graphicsPipeLineState.set(id, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(unsigned int id)
	{
		m_vertexBuffer.set(id, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(unsigned int id)
	{
		m_indexBuffer.set(id, m_commandList);
	}

	void DX3DBaseObjects::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_descriptorHeap.set(m_device, m_commandList, heapParamArray);
	}

	void DX3DBaseObjects::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_commandList->IASetPrimitiveTopology(topology);
	}

	void DX3DBaseObjects::drawIndexedInstanced(unsigned int indexCountPerInstance, unsigned int instanceCount, unsigned int startIndexLocation, unsigned int baseVertexLocation, unsigned int startInstanceLocation)
	{
		m_commandList->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
	}
}