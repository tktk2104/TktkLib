#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

#include <TktkFileIo/lodepng.h>

#include <stdexcept>
#include <vector>

namespace tktk
{
	constexpr unsigned int commandListCount{ 1 };

	struct VertexData
	{
		tktkMath::Vector3 pos;
		tktkMath::Vector2 uv;
	};

	DX3DBaseObjects::DX3DBaseObjects(HWND hwnd, const tktkMath::Vector2& windowSize)
	{
		m_viewport.Width = windowSize.x;
		m_viewport.Height = windowSize.y;
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.MaxDepth = 1.0f;
		m_viewport.MinDepth = 0.0f;

		m_scissorrect.top = 0;
		m_scissorrect.left = 0;
		m_scissorrect.right = m_scissorrect.left + static_cast<long>(windowSize.x);
		m_scissorrect.bottom = m_scissorrect.top + static_cast<long>(windowSize.y);

#ifdef _DEBUG

		{
			ID3D12Debug* debugLayer{ nullptr };
			D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
			debugLayer->EnableDebugLayer();
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
		{
			D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
			commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			commandQueueDesc.NodeMask = 0;
			commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		}
		
		// スワップチェーンを作る
		{
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
			swapChainDesc.Width = static_cast<unsigned int>(windowSize.x);
			swapChainDesc.Height = static_cast<unsigned int>(windowSize.y);
			swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
			swapChainDesc.BufferCount = backBufferCount;
			swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			m_factory->CreateSwapChainForHwnd(m_commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, &m_swapChain);
		}

		// フェンスを作成する
		m_device->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));

		// バックバッファー用のレンダーターゲットビューを作る
		{
			D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc{};
			renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			renderTargetViewHeapDesc.NodeMask = 0;
			renderTargetViewHeapDesc.NumDescriptors = 2;
			renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			m_device->CreateDescriptorHeap(&renderTargetViewHeapDesc, IID_PPV_ARGS(&m_backBufferRenderTargetViewHeap));
		}

		// スワップチェーンのバックバッファーとバックバッファー用のレンダーターゲットビューを結びつける
		for (unsigned int i = 0; i < backBufferCount; ++i)
		{
			// スワップチェーンのｉ番目のバックバッファーを取得する
			m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_backBuffers.at(i)));

			// バックバッファー用のレンダーターゲットビューのｉ番目のビューのアドレスを求める
			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_backBufferRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
			handle.ptr += i * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			// ｉ番目のスワップチェーンのバックバッファーとバックバッファー用のレンダーターゲットビューを結びつける
			m_device->CreateRenderTargetView(m_backBuffers.at(i), nullptr, handle);
		}

		// 初回リセット
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// 描画する頂点の配列
		VertexData vertices[] =
		{
			{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
			{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
			{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
			{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
		};

		// 頂点バッファを作る
		ID3D12Resource* vertexBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Width = sizeof(vertices);
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.SampleDesc.Count = 1;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			m_device->CreateCommittedResource(
				&heapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&vertexBuffer)
			);

			VertexData* vertMap{ nullptr };
			vertexBuffer->Map(0, nullptr, (void**)(&vertMap));
			std::copy(std::begin(vertices), std::end(vertices), vertMap);
			vertexBuffer->Unmap(0, nullptr);
		}

		// 作った頂点バッファを頂点バッファビューに設定する
		m_vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = sizeof(vertices);
		m_vertexBufferView.StrideInBytes = sizeof(vertices[0]);


		// 描画する頂点のインデックス
		unsigned short indices[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		// インデックスバッファを作る
		ID3D12Resource* indexBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Width = sizeof(indices);
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.SampleDesc.Count = 1;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			m_device->CreateCommittedResource(
				&heapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&indexBuffer)
			);

			unsigned short* mappedIndex{ nullptr };
			indexBuffer->Map(0, nullptr, (void**)&mappedIndex);
			std::copy(std::begin(indices), std::end(indices), mappedIndex);
			indexBuffer->Unmap(0, nullptr);
		}
		// 作ったインデックスバッファをインデックスバッファビューに設定する
		m_indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		m_indexBufferView.SizeInBytes = sizeof(indices);

		// ディスクリプタレンジを作る
		D3D12_DESCRIPTOR_RANGE descTblRange{};
		descTblRange.NumDescriptors = 1;
		descTblRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descTblRange.BaseShaderRegister = 0;
		descTblRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// ルートパラメーターを作る
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		rootParam.DescriptorTable.pDescriptorRanges = &descTblRange;
		rootParam.DescriptorTable.NumDescriptorRanges = 1;

		// サンプラーを作る
		D3D12_STATIC_SAMPLER_DESC samplerDesc{};
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;

		// ルートシグネチャを作る
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		rootSignatureDesc.pParameters = &rootParam;
		rootSignatureDesc.NumParameters = 1;
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
		ID3DBlob* rootSigBlob{ nullptr };
		ID3DBlob* errorBlob{ nullptr };
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		auto test = m_device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
		rootSigBlob->Release();

		// 頂点シェーダーを読み込む
		ID3DBlob* vsBlob{ nullptr };
		std::vector<char> vsByteArray;
		{
			std::FILE* fp;

			int ret = fopen_s(&fp, "res/BasicVertexShader.cso", "rb");

			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}

			fseek(fp, 0, SEEK_END);
			vsByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);

			fread(vsByteArray.data(), vsByteArray.size(), 1, fp);
			fclose(fp);
		}

		// ピクセルシェーダーを読み込む
		ID3DBlob* psBlob{ nullptr };
		std::vector<char> psByteArray;
		{
			std::FILE* fp;

			int ret = fopen_s(&fp, "res/BasicPixelShader.cso", "rb");

			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}

			fseek(fp, 0, SEEK_END);
			psByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);

			fread(psByteArray.data(), psByteArray.size(), 1, fp);
			fclose(fp);
		}

		// グラフィックパイプラインを作る
		{
			D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipeLineStateDesc{};
			graphicsPipeLineStateDesc.pRootSignature = m_rootSignature;
			graphicsPipeLineStateDesc.VS.pShaderBytecode = vsByteArray.data();
			graphicsPipeLineStateDesc.VS.BytecodeLength = vsByteArray.size();
			graphicsPipeLineStateDesc.PS.pShaderBytecode = psByteArray.data();
			graphicsPipeLineStateDesc.PS.BytecodeLength = psByteArray.size();
			graphicsPipeLineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
			graphicsPipeLineStateDesc.RasterizerState.MultisampleEnable = false;
			graphicsPipeLineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
			graphicsPipeLineStateDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
			graphicsPipeLineStateDesc.RasterizerState.DepthClipEnable = true;
			graphicsPipeLineStateDesc.BlendState.AlphaToCoverageEnable = false;
			graphicsPipeLineStateDesc.BlendState.IndependentBlendEnable = false;

			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			graphicsPipeLineStateDesc.BlendState.RenderTarget[0] = renderTargetBlendDesc;

			D3D12_INPUT_ELEMENT_DESC inputLayout[]{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};

			graphicsPipeLineStateDesc.InputLayout.pInputElementDescs = inputLayout;
			graphicsPipeLineStateDesc.InputLayout.NumElements = _countof(inputLayout);
			graphicsPipeLineStateDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
			graphicsPipeLineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			graphicsPipeLineStateDesc.NumRenderTargets = 1;
			graphicsPipeLineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			graphicsPipeLineStateDesc.SampleDesc.Count = 1;
			graphicsPipeLineStateDesc.SampleDesc.Quality = 0;

			m_device->CreateGraphicsPipelineState(&graphicsPipeLineStateDesc, IID_PPV_ARGS(&m_pipeLineState));
		}

		// テクスチャをロードする
		std::vector<unsigned char> textureData;
		unsigned int width;
		unsigned int height;
		auto error = lodepng::decode(textureData, width, height, "res/test.png");
		if (error != 0)
		{
			throw std::runtime_error("can not open res/test.png");
		}

#if TRUE

		// テクスチャバッファを作る
		ID3D12Resource* textureBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES uploadHeapProp{};
			uploadHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			uploadHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadHeapProp.CreationNodeMask = 0;
			uploadHeapProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Width = textureData.size();
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;

			ID3D12Resource* uploadBuff{ nullptr };
			m_device->CreateCommittedResource(
				&uploadHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&uploadBuff)
			);

			D3D12_HEAP_PROPERTIES texHeapProp{};
			texHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
			texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			texHeapProp.CreationNodeMask = 0;
			texHeapProp.VisibleNodeMask = 0;

			resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			resDesc.Width = width;
			resDesc.Height = height;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

			HRESULT test = m_device->CreateCommittedResource(
				&texHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&textureBuffer)
			);

			uint8_t* mapForImg{ nullptr };
			uploadBuff->Map(0, nullptr, (void**)&mapForImg);
			std::copy_n(textureData.data(), textureData.size(), mapForImg);
			uploadBuff->Unmap(0, nullptr);

			D3D12_TEXTURE_COPY_LOCATION src{};
			src.pResource = uploadBuff;
			src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
			src.PlacedFootprint.Offset = 0;
			src.PlacedFootprint.Footprint.Width = width;
			src.PlacedFootprint.Footprint.Height = height;
			src.PlacedFootprint.Footprint.Depth = 1;
			src.PlacedFootprint.Footprint.RowPitch = width * 4;
			src.PlacedFootprint.Footprint.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			D3D12_TEXTURE_COPY_LOCATION dst{};
			dst.pResource = textureBuffer;
			dst.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
			dst.SubresourceIndex = 0;

			m_commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

			D3D12_RESOURCE_BARRIER barrierDesc{};
			barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrierDesc.Transition.pResource = textureBuffer;
			barrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
			barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
			m_commandList->ResourceBarrier(1, &barrierDesc);

			m_commandList->Close();

			ID3D12CommandList* commandLists[] = { m_commandList };
			m_commandQueue->ExecuteCommandLists(1, commandLists);

			// GPU処理が終わった事を検知するための準備
			m_commandQueue->Signal(m_fence, ++m_fenceVal);

			// もしGPU処理が終わっていなければ
			if (m_fence->GetCompletedValue() != m_fenceVal)
			{
				// イベントを作ってそのハンドルを取得
				auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

				// フェンスにGPU処理が終わったらイベントを発生させる事を設定する
				m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

				// フェンスに指定したイベントが発生するまで無限に待ち続ける
				WaitForSingleObject(eventHandle, INFINITE);

				// イベントハンドルを閉じる
				CloseHandle(eventHandle);
			}

			// コマンドアロケータをリセットする
			m_commandAllocator->Reset();

			// コマンドリストをリセットする
			m_commandList->Reset(m_commandAllocator, nullptr);
		}

#else

		// テクスチャバッファを作る
		ID3D12Resource* textureBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
			heapProp.CreationNodeMask = 0;
			heapProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			resDesc.Width = width;
			resDesc.Height = height;
			resDesc.DepthOrArraySize = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.MipLevels = 1;
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

			m_device->CreateCommittedResource(
				&heapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
				nullptr,
				IID_PPV_ARGS(&textureBuffer)
			);

			textureBuffer->WriteToSubresource(
				0,
				nullptr,
				textureData.data(),
				width * 4, //rowp
				textureData.size() //slicep
			);
		}

#endif

		HRESULT temp;

		// テクスチャバッファビューを作る
		{
			D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
			descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descHeapDesc.NodeMask = 0;
			descHeapDesc.NumDescriptors = 1;
			descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			temp = m_device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_texDescHeap));
		}

		// シェーダーリソースビューを作る
		{
			D3D12_SHADER_RESOURCE_VIEW_DESC shaderResouseViewDesc{};
			shaderResouseViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			shaderResouseViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			shaderResouseViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			shaderResouseViewDesc.Texture2D.MipLevels = 1;

			m_device->CreateShaderResourceView(
				textureBuffer,
				&shaderResouseViewDesc,
				m_texDescHeap->GetCPUDescriptorHandleForHeapStart()
			);
		}
	}

	DX3DBaseObjects::~DX3DBaseObjects()
	{
		if (m_pipeLineState != nullptr)
		{
			m_pipeLineState->Release();
		}
		if (m_rootSignature != nullptr)
		{
			m_rootSignature->Release();
		}

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
		if (m_fence != nullptr)
		{
			m_fence->Release();
		}
		if (m_commandQueue != nullptr)
		{
			m_commandQueue->Release();
		}
		if (m_swapChain != nullptr)
		{
			m_swapChain->Release();
		}
		if (m_backBufferRenderTargetViewHeap != nullptr)
		{
			m_backBufferRenderTargetViewHeap->Release();
		}
	}

	void DX3DBaseObjects::beginDraw()
	{
		// 現在のバックバッファーのインデックスを取得する
		m_curBackBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();

		// 現在のバックバッファー用のレンダーターゲットビューのハンドルを取得する
		auto curBackBufferRenderTargetViewHeapHandle = m_backBufferRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
		curBackBufferRenderTargetViewHeapHandle.ptr += m_curBackBufferIndex * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	
		// バックバッファー用のレンダーターゲットビューのリソースバリアを設定する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_backBuffers.at(m_curBackBufferIndex);
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_commandList->ResourceBarrier(1, &barrierDesc);

		// 現在のバックバッファーを描画先に設定する
		m_commandList->OMSetRenderTargets(1, &curBackBufferRenderTargetViewHeapHandle, true, nullptr);

		// 現在のバックバッファーを指定した単色で塗りつぶす
		float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_commandList->ClearRenderTargetView(curBackBufferRenderTargetViewHeapHandle, clearColor, 0, nullptr);
		
		// レンダリングパイプラインステートを設定する
		m_commandList->SetPipelineState(m_pipeLineState);
		
		// グラフィックパイプラインにルートシグネチャを設定する
		m_commandList->SetGraphicsRootSignature(m_rootSignature);
		
		// グラフィックパイプラインにディスクリプタヒープを設定する
		m_commandList->SetDescriptorHeaps(1, &m_texDescHeap);
		
		// ルートパラメーターとディスクリプタヒープを関連付ける
		m_commandList->SetGraphicsRootDescriptorTable(0, m_texDescHeap->GetGPUDescriptorHandleForHeapStart());
		
		// トライアングルリストで描画するように設定する
		m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// 頂点バッファ情報を設定する
		m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
		
		// インデックスバッファ情報を設定する
		m_commandList->IASetIndexBuffer(&m_indexBufferView);
		
		// ビューポートを設定する
		m_commandList->RSSetViewports(1, &m_viewport);
		
		// シザー矩形を設定する
		m_commandList->RSSetScissorRects(1, &m_scissorrect);
		
		// 描画
		m_commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}

	void DX3DBaseObjects::endDraw()
	{
		// バックバッファー用のレンダーターゲットビューのリソースバリアを解除する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_backBuffers.at(m_curBackBufferIndex);
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		m_commandList->ResourceBarrier(1, &barrierDesc);

		// コマンドリストを閉じる
		m_commandList->Close();

		// コマンドリストをコマンドキューに渡す
		std::array<ID3D12CommandList*, commandListCount> commandLists = { m_commandList };
		m_commandQueue->ExecuteCommandLists(commandListCount, commandLists.data());

		// GPU処理が終わった事を検知するための準備
		m_commandQueue->Signal(m_fence, ++m_fenceVal);

		// もしGPU処理が終わっていなければ
		if (m_fence->GetCompletedValue() != m_fenceVal)
		{
			// イベントを作ってそのハンドルを取得
			auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

			// フェンスにGPU処理が終わったらイベントを発生させる事を設定する
			m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

			// フェンスに指定したイベントが発生するまで無限に待ち続ける
			WaitForSingleObject(eventHandle, INFINITE);

			// イベントハンドルを閉じる
			CloseHandle(eventHandle);
		}

		// コマンドアロケータをリセットする
		m_commandAllocator->Reset();

		// コマンドリストをリセットする
		m_commandList->Reset(m_commandAllocator, nullptr);
		
		// 画面をフリップする
		m_swapChain->Present(1, 0);
	}
}