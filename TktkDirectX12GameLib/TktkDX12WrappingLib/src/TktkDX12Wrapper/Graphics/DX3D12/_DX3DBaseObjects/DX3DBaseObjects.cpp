#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DResourceInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor)
		: m_dX3DResource(initParam)
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
		m_dX3DResource.createViewport(getSystemId(SystemViewportType::Basic), { { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// シザー矩形を作る
		m_dX3DResource.createScissorRect(getSystemId(SystemScissorRectType::Basic), { { tktkMath::vec2Zero, windowSize } });

		// スワップチェーンのバックバッファーをディスクリプタヒープで使うための準備
		m_dX3DResource.createRtBuffer(getSystemId(SystemRenderTargetBufferType::BackBuffer_1), m_swapChain, 0U);
		m_dX3DResource.createRtBuffer(getSystemId(SystemRenderTargetBufferType::BackBuffer_2), m_swapChain, 1U);

		// バックバッファー用のディスクリプタヒープを作る
		{
			RtvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.resize(2U);
			initParam.descriptorParamArray.at(0U).type = RtvDescriptorType::normal;
			initParam.descriptorParamArray.at(0U).id = getSystemId(SystemRenderTargetBufferType::BackBuffer_1);
			initParam.descriptorParamArray.at(1U).type = RtvDescriptorType::normal;
			initParam.descriptorParamArray.at(1U).id = getSystemId(SystemRenderTargetBufferType::BackBuffer_2);

			m_dX3DResource.createRtvDescriptorHeap(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), m_device, initParam);
		}

		// デフォルトの深度バッファーを作る
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = windowSize;
			initParam.useAsShaderResource = false;

			m_dX3DResource.createDsBuffer(getSystemId(SystemDepthStencilBufferType::Basic), m_device, initParam);
		}

		// デフォルトの深度ディスクリプタヒープを作る
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemId(SystemDepthStencilBufferType::Basic) });

			m_dX3DResource.createDsvDescriptorHeap(getSystemId(SystemDsvDescriptorHeapType::Basic), m_device, initParam);
		}

		// 白テクスチャを作る
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			TexBuffData dataParam{};
			dataParam.textureData = {
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255
			};
			dataParam.width = 4U;
			dataParam.height = 4U;

			m_dX3DResource.cpuPriorityCreateTextureBuffer(getSystemId(SystemTextureBufferType::White), m_device, formatParam, dataParam);
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
		
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_curBackBufferIndex == 0) ? SystemRenderTargetBufferType::BackBuffer_1 : SystemRenderTargetBufferType::BackBuffer_2;
		
		// バックバッファをレンダーターゲット状態にする
		m_dX3DResource.beginWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// 現在のバックバッファーをを描画先に設定する
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_curBackBufferIndex);

		// 現在のバックバッファーを指定した単色で塗りつぶす
		m_dX3DResource.clearRtv(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), m_device, m_commandList, m_curBackBufferIndex, m_backGroundColor);
		
		// 全てのデプスステンシルビューをクリアする
		m_dX3DResource.clearDsvAll(m_device, m_commandList);

		// ビューポートを設定する
		m_dX3DResource.setViewport(getSystemId(SystemViewportType::Basic), m_commandList);
		
		// シザー矩形を設定する
		m_dX3DResource.setScissorRect(getSystemId(SystemScissorRectType::Basic), m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// 現在のバックバッファーの種類を「m_curBackBufferIndex」から求める
		auto curBackBufferType = (m_curBackBufferIndex == 0) ? SystemRenderTargetBufferType::BackBuffer_1 : SystemRenderTargetBufferType::BackBuffer_2;
		
		// バックバッファをプリセット状態にする
		m_dX3DResource.endWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// コマンドリストを実行する
		executeCommandList();

		// 画面をフリップする
		m_swapChain->Present(1, 0);
	}

	void DX3DBaseObjects::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dX3DResource.createRootSignature(id, m_device, initParam);
	}

	void DX3DBaseObjects::createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dX3DResource.createPipeLineState(id, m_device, initParam, shaderFilePath);

		// 初回セット（※最初にセットした時のみ重たい処理となるので、作成直後に先行でセットする）
		m_dX3DResource.setPipeLineState(id, m_commandList);
	}

	void DX3DBaseObjects::createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dX3DResource.createVertexBuffer(id, m_device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dX3DResource.createIndexBuffer(id, m_device, indices);
	}

	void DX3DBaseObjects::createCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.createCBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_dX3DResource.createRtBuffer(id, m_device, renderTargetSize, clearColor);
	}

	void DX3DBaseObjects::createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam)
	{
		m_dX3DResource.createDsBuffer(id, m_device, initParam);
	}

	void DX3DBaseObjects::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createBasicDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createRtvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createDsvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dX3DResource.cpuPriorityCreateTextureBuffer(id, m_device, formatParam, dataParam);
	}

	void DX3DBaseObjects::gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_dX3DResource.gpuPriorityCreateTextureBuffer(id, m_device, m_commandList, formatParam, dataParam);
	}

	void DX3DBaseObjects::cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dX3DResource.cpuPriorityLoadTextureBuffer(id, m_device, texDataPath);
	}

	void DX3DBaseObjects::gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath)
	{
		m_dX3DResource.gpuPriorityLoadTextureBuffer(id, m_device, m_commandList, texDataPath);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.updateCBuffer(id, m_device, m_commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dX3DResource.clearRtv(id, m_device, m_commandList, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getTextureBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDsBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getDsBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRtBufferSizePx(unsigned int id) const
	{
		return m_dX3DResource.getRtBufferSizePx(id);
	}

	void DX3DBaseObjects::setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.setRtv(rtvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.setRtvAndDsv(dsvDescriptorHeapId, dsvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDsv(unsigned int id)
	{
		m_dX3DResource.setOnlyDsv(id, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBufferView()
	{
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId)
	{
		m_dX3DResource.setBackBufferViewAndDsv(dsvDescriptorHeapId, m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.unSetRtv(rtvDescriptorHeapId, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDsv(unsigned int dsvDescriptorHeapId)
	{
		m_dX3DResource.unSetDsv(dsvDescriptorHeapId, m_commandList);
	}

	void DX3DBaseObjects::setViewport(unsigned int id)
	{
		m_dX3DResource.setViewport(id, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(unsigned int id)
	{
		m_dX3DResource.setScissorRect(id, m_commandList);
	}

	void DX3DBaseObjects::setPipeLineState(unsigned int id)
	{
		m_dX3DResource.setPipeLineState(id, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(unsigned int id)
	{
		m_dX3DResource.setVertexBuffer(id, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(unsigned int id)
	{
		m_dX3DResource.setIndexBuffer(id, m_commandList);
	}

	void DX3DBaseObjects::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_dX3DResource.setDescriptorHeap(m_device, m_commandList, heapParamArray);
	}

	void DX3DBaseObjects::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_commandList->IASetPrimitiveTopology(topology);
	}

	void DX3DBaseObjects::drawIndexedInstanced(unsigned int indexCountPerInstance, unsigned int instanceCount, unsigned int startIndexLocation, unsigned int baseVertexLocation, unsigned int startInstanceLocation)
	{
		m_commandList->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
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

		// コピー元バッファを削除する
		m_dX3DResource.deleteUploadBufferAll();
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemViewportType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemScissorRectType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemVertexBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemIndexBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemConstantBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemTextureBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRenderTargetBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemDepthStencilBufferType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemBasicDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRtvDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemDsvDescriptorHeapType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemRootSignatureType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}

	unsigned int DX3DBaseObjects::getSystemId(SystemPipeLineStateType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}
}