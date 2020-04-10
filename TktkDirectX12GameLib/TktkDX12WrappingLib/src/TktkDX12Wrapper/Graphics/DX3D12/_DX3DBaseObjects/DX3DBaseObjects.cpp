#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

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


		// �f�o�C�X�����
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));

		// �t�@�N�g�������
#ifdef _DEBUG
		CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
#else
		CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#endif

		// �R�}���h�A���P�[�^�����
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

		// �R�}���h���X�g�����
		m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

		// �R�}���h�L���[�����
		{
			D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
			commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			commandQueueDesc.NodeMask = 0;
			commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		}
		
		// �X���b�v�`�F�[�������
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

		// �t�F���X���쐬����
		m_device->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));

		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�����
		{
			D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc{};
			renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			renderTargetViewHeapDesc.NodeMask = 0;
			renderTargetViewHeapDesc.NumDescriptors = 2;
			renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			m_device->CreateDescriptorHeap(&renderTargetViewHeapDesc, IID_PPV_ARGS(&m_backBufferRenderTargetViewHeap));
		}

		// �X���b�v�`�F�[���̃o�b�N�o�b�t�@�[�ƃo�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�����т���
		for (unsigned int i = 0; i < backBufferCount; ++i)
		{
			// �X���b�v�`�F�[���̂��Ԗڂ̃o�b�N�o�b�t�@�[���擾����
			m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_backBuffers.at(i)));

			// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�̂��Ԗڂ̃r���[�̃A�h���X�����߂�
			D3D12_CPU_DESCRIPTOR_HANDLE handle = m_backBufferRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
			handle.ptr += i * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

			// ���Ԗڂ̃X���b�v�`�F�[���̃o�b�N�o�b�t�@�[�ƃo�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�����т���
			m_device->CreateRenderTargetView(m_backBuffers.at(i), nullptr, handle);
		}

		// ���񃊃Z�b�g
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// �`�悷�钸�_�̔z��
		VertexData vertices[] =
		{
			{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
			{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
			{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
			{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
		};

		// ���_�o�b�t�@�����
		ID3D12Resource* vertexBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = sizeof(vertices);
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
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

		// ��������_�o�b�t�@�𒸓_�o�b�t�@�r���[�ɐݒ肷��
		m_vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = sizeof(vertices);
		m_vertexBufferView.StrideInBytes = sizeof(vertices[0]);


		// �`�悷�钸�_�̃C���f�b�N�X
		unsigned short indices[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		// �C���f�b�N�X�o�b�t�@�����
		ID3D12Resource* indexBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = sizeof(indices);
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
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
		// ������C���f�b�N�X�o�b�t�@���C���f�b�N�X�o�b�t�@�r���[�ɐݒ肷��
		m_indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
		m_indexBufferView.SizeInBytes = sizeof(indices);

		// �f�B�X�N���v�^�����W�����
		D3D12_DESCRIPTOR_RANGE descTblRange[2]{};
		descTblRange[0].NumDescriptors = 1;
		descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descTblRange[0].BaseShaderRegister = 0;
		descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		descTblRange[1].NumDescriptors = 1;
		descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		descTblRange[1].BaseShaderRegister = 0;
		descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

		// ���[�g�p�����[�^�[�����
		D3D12_ROOT_PARAMETER rootParam[2]{};
		rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		rootParam[0].DescriptorTable.pDescriptorRanges = &descTblRange[0];
		rootParam[0].DescriptorTable.NumDescriptorRanges = 1;
		rootParam[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParam[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		rootParam[1].DescriptorTable.pDescriptorRanges = &descTblRange[1];
		rootParam[1].DescriptorTable.NumDescriptorRanges = 1;

		// �T���v���[�����
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

		// ���[�g�V�O�l�`�������
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		rootSignatureDesc.pParameters = rootParam;
		rootSignatureDesc.NumParameters = 2;
		rootSignatureDesc.pStaticSamplers = &samplerDesc;
		rootSignatureDesc.NumStaticSamplers = 1;
		ID3DBlob* rootSigBlob{ nullptr };
		ID3DBlob* errorBlob{ nullptr };
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		auto test = m_device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));
		rootSigBlob->Release();

		// ���_�V�F�[�_�[��ǂݍ���
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

		// �s�N�Z���V�F�[�_�[��ǂݍ���
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

		// �O���t�B�b�N�p�C�v���C�������
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

		// �e�N�X�`�������[�h����
		std::vector<unsigned char> textureData;
		unsigned int width;
		unsigned int height;
		auto error = lodepng::decode(textureData, width, height, "res/test.png");
		if (error != 0)
		{
			throw std::runtime_error("can not open res/test.png");
		}

#if TRUE

		// �e�N�X�`���o�b�t�@�����
		ID3D12Resource* textureBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES uploadHeapProp{};
			uploadHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			uploadHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadHeapProp.CreationNodeMask = 0;
			uploadHeapProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = textureData.size();
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

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

			// GPU�������I������������m���邽�߂̏���
			m_commandQueue->Signal(m_fence, ++m_fenceVal);

			// ����GPU�������I����Ă��Ȃ����
			if (m_fence->GetCompletedValue() != m_fenceVal)
			{
				// �C�x���g������Ă��̃n���h�����擾
				auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

				// �t�F���X��GPU�������I�������C�x���g�𔭐������鎖��ݒ肷��
				m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

				// �t�F���X�Ɏw�肵���C�x���g����������܂Ŗ����ɑ҂�������
				WaitForSingleObject(eventHandle, INFINITE);

				// �C�x���g�n���h�������
				CloseHandle(eventHandle);
			}

			// �R�}���h�A���P�[�^�����Z�b�g����
			m_commandAllocator->Reset();

			// �R�}���h���X�g�����Z�b�g����
			m_commandList->Reset(m_commandAllocator, nullptr);
		}

#else

		// �e�N�X�`���o�b�t�@�����
		ID3D12Resource* textureBuffer{ nullptr };
		{
			D3D12_HEAP_PROPERTIES heapProp{};
			heapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
			heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
			heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
			heapProp.CreationNodeMask = 0;
			heapProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			resDesc.Width = width;
			resDesc.Height = height;
			resDesc.DepthOrArraySize = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.MipLevels = 1;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

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

		tktkMath::Matrix4 mat = tktkMath::mat4Identity;

		ID3D12Resource* constBuff{ nullptr };
		{
			D3D12_HEAP_PROPERTIES constBuffHeapProp{};
			constBuffHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
			constBuffHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			constBuffHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			constBuffHeapProp.CreationNodeMask = 0;
			constBuffHeapProp.VisibleNodeMask = 0;

			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format = DXGI_FORMAT_UNKNOWN;
			resDesc.Width = (sizeof(mat) + 0xff) & ~0xff;
			resDesc.Height = 1;
			resDesc.DepthOrArraySize = 1;
			resDesc.MipLevels = 1;
			resDesc.SampleDesc.Count = 1;
			resDesc.SampleDesc.Quality = 0;
			resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			m_device->CreateCommittedResource(
				&constBuffHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&constBuff)
			);

			tktkMath::Matrix4* mappedMatrix{ nullptr };
			constBuff->Map(0, nullptr, (void**)&mappedMatrix);
			*mappedMatrix = mat;
			constBuff->Unmap(0, nullptr);
		}

		// �f�B�X�N���v�^�q�[�v�����
		{
			D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
			descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			descHeapDesc.NodeMask = 0;
			descHeapDesc.NumDescriptors = 2;
			descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			m_device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&m_basicDescHeap));
		}

		auto basicHeapHandle = m_basicDescHeap->GetCPUDescriptorHandleForHeapStart();

		// �V�F�[�_�[���\�[�X�r���[�����
		{
			D3D12_SHADER_RESOURCE_VIEW_DESC shaderResouseViewDesc{};
			shaderResouseViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			shaderResouseViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			shaderResouseViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			shaderResouseViewDesc.Texture2D.MipLevels = 1;

			m_device->CreateShaderResourceView(
				textureBuffer,
				&shaderResouseViewDesc,
				basicHeapHandle
			);
		}

		basicHeapHandle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		// �R���X�^���g�o�b�t�@�[�r���[�����
		{
			D3D12_CONSTANT_BUFFER_VIEW_DESC constantBufferViewDesc{};
			constantBufferViewDesc.BufferLocation = constBuff->GetGPUVirtualAddress();
			constantBufferViewDesc.SizeInBytes = static_cast<UINT>(constBuff->GetDesc().Width);

			m_device->CreateConstantBufferView(
				&constantBufferViewDesc,
				basicHeapHandle
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
		// ���݂̃o�b�N�o�b�t�@�[�̃C���f�b�N�X���擾����
		m_curBackBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();

		// ���݂̃o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�̃n���h�����擾����
		auto curBackBufferRenderTargetViewHeapHandle = m_backBufferRenderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
		curBackBufferRenderTargetViewHeapHandle.ptr += m_curBackBufferIndex * m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	
		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�̃��\�[�X�o���A��ݒ肷��
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_backBuffers.at(m_curBackBufferIndex);
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		m_commandList->ResourceBarrier(1, &barrierDesc);

		// ���݂̃o�b�N�o�b�t�@�[��`���ɐݒ肷��
		m_commandList->OMSetRenderTargets(1, &curBackBufferRenderTargetViewHeapHandle, true, nullptr);

		// ���݂̃o�b�N�o�b�t�@�[���w�肵���P�F�œh��Ԃ�
		float clearColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_commandList->ClearRenderTargetView(curBackBufferRenderTargetViewHeapHandle, clearColor, 0, nullptr);
		
		// �����_�����O�p�C�v���C���X�e�[�g��ݒ肷��
		m_commandList->SetPipelineState(m_pipeLineState);
		
		// �O���t�B�b�N�p�C�v���C���Ƀ��[�g�V�O�l�`����ݒ肷��
		m_commandList->SetGraphicsRootSignature(m_rootSignature);
		
		// �O���t�B�b�N�p�C�v���C���Ƀf�B�X�N���v�^�q�[�v��ݒ肷��
		m_commandList->SetDescriptorHeaps(1, &m_basicDescHeap);
		
		// ���[�g�p�����[�^�[�ƃf�B�X�N���v�^�q�[�v���֘A�t����
		auto heapHandle = m_basicDescHeap->GetGPUDescriptorHandleForHeapStart();
		m_commandList->SetGraphicsRootDescriptorTable(0, heapHandle);
		heapHandle.ptr += m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		m_commandList->SetGraphicsRootDescriptorTable(1, heapHandle);
		
		// �g���C�A���O�����X�g�ŕ`�悷��悤�ɐݒ肷��
		m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// ���_�o�b�t�@����ݒ肷��
		m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
		
		// �C���f�b�N�X�o�b�t�@����ݒ肷��
		m_commandList->IASetIndexBuffer(&m_indexBufferView);
		
		// �r���[�|�[�g��ݒ肷��
		m_commandList->RSSetViewports(1, &m_viewport);
		
		// �V�U�[��`��ݒ肷��
		m_commandList->RSSetScissorRects(1, &m_scissorrect);
		
		// �`��
		m_commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}

	void DX3DBaseObjects::endDraw()
	{
		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�̃��\�[�X�o���A����������
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_backBuffers.at(m_curBackBufferIndex);
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		m_commandList->ResourceBarrier(1, &barrierDesc);

		// �R�}���h���X�g�����
		m_commandList->Close();

		// �R�}���h���X�g���R�}���h�L���[�ɓn��
		std::array<ID3D12CommandList*, commandListCount> commandLists = { m_commandList };
		m_commandQueue->ExecuteCommandLists(commandListCount, commandLists.data());

		// GPU�������I������������m���邽�߂̏���
		m_commandQueue->Signal(m_fence, ++m_fenceVal);

		// ����GPU�������I����Ă��Ȃ����
		if (m_fence->GetCompletedValue() != m_fenceVal)
		{
			// �C�x���g������Ă��̃n���h�����擾
			auto eventHandle = CreateEvent(nullptr, false, false, nullptr);

			// �t�F���X��GPU�������I�������C�x���g�𔭐������鎖��ݒ肷��
			m_fence->SetEventOnCompletion(m_fenceVal, eventHandle);

			// �t�F���X�Ɏw�肵���C�x���g����������܂Ŗ����ɑ҂�������
			WaitForSingleObject(eventHandle, INFINITE);

			// �C�x���g�n���h�������
			CloseHandle(eventHandle);
		}

		// �R�}���h�A���P�[�^�����Z�b�g����
		m_commandAllocator->Reset();

		// �R�}���h���X�g�����Z�b�g����
		m_commandList->Reset(m_commandAllocator, nullptr);
		
		// ��ʂ��t���b�v����
		m_swapChain->Present(1, 0);
	}
}