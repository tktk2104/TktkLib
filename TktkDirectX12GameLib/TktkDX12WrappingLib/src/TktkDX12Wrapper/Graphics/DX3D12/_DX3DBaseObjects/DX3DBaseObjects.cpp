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

		// �r���[�|�[�g�����
		m_viewport.create<0>({ { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// �V�U�[��`�����
		m_scissorRect.create<0>({ { tktkMath::vec2Zero, windowSize } });

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
		std::vector<VertexData> vertices =
		{
			{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
			{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
			{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
			{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
		};
		m_vertexBuffer.create<0>(m_device, vertices);

		// �`�悷�钸�_�̃C���f�b�N�X
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		m_indexBuffer.create<0>(m_device, indices);

		// ���[�g�V�O�l�`�������
		{
			RootSignatureInitParam initParam{};
			initParam.m_flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			initParam.m_rootParamArray.resize(2U);
			{
				initParam.m_rootParamArray.at(0).m_shaderVisibility		= D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.m_rootParamArray.at(0).m_descriptorTableArray.resize(1U);
				{
					initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_numDescriptors	= 1;
					initParam.m_rootParamArray.at(0).m_descriptorTableArray.at(0).m_type			= D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				}
			}
			{
				initParam.m_rootParamArray.at(1).m_shaderVisibility		= D3D12_SHADER_VISIBILITY_VERTEX;
				initParam.m_rootParamArray.at(1).m_descriptorTableArray.resize(1U);
				{
					initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_numDescriptors	= 1;
					initParam.m_rootParamArray.at(1).m_descriptorTableArray.at(0).m_type			= D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				}
			}
			initParam.m_samplerDescArray.resize(1U);
			{
				initParam.m_samplerDescArray.at(0).m_addressU			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.m_samplerDescArray.at(0).m_addressV			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.m_samplerDescArray.at(0).m_addressW			= D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.m_samplerDescArray.at(0).m_bordercolor		= D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
				initParam.m_samplerDescArray.at(0).m_filter				= D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				initParam.m_samplerDescArray.at(0).m_maxLod				= D3D12_FLOAT32_MAX;
				initParam.m_samplerDescArray.at(0).m_minLod				= 0.0f;
				initParam.m_samplerDescArray.at(0).m_shaderVisibility	= D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.m_samplerDescArray.at(0).m_comparisonFunc		= D3D12_COMPARISON_FUNC_NEVER;
			}

			m_graphicsPipeLineState.createRootSignature<0>(m_device, initParam);
		}

		// �O���t�B�b�N�p�C�v���C�������
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			GraphicsPipeLineStateInitParam initParam{};
			initParam.m_rasterizerDesc.MultisampleEnable = false;
			initParam.m_rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
			initParam.m_rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
			initParam.m_rasterizerDesc.DepthClipEnable = true;
			initParam.m_blendDesc.AlphaToCoverageEnable = false;
			initParam.m_blendDesc.IndependentBlendEnable = false;
			initParam.m_blendDesc.RenderTarget[0] = renderTargetBlendDesc;
			initParam.m_inputLayoutArray = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	  0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			initParam.m_primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			initParam.m_renderTargetFormatArray = {
				DXGI_FORMAT_R8G8B8A8_UNORM
			};

			m_graphicsPipeLineState.createGraphicsPipeLineState<0, 0>(
				m_device,
				initParam,
				"res/BasicVertexShader.cso",
				"res/BasicPixelShader.cso"
				);
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
		m_graphicsPipeLineState.set<0>(m_commandList);
		
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
		m_vertexBuffer.set<0>(m_commandList);
		
		// �C���f�b�N�X�o�b�t�@����ݒ肷��
		m_indexBuffer.set<0>(m_commandList);
		
		// �r���[�|�[�g��ݒ肷��
		m_viewport.set<0>(m_commandList);
		
		// �V�U�[��`��ݒ肷��
		m_scissorRect.set<0>(m_commandList);
		
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