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

	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize)
		: m_viewport(initParam.viewPortNum)
		, m_scissorRect(initParam.scissorRectNum)
		, m_vertexBuffer(initParam.vertexBufferNum)
		, m_indexBuffer(initParam.indexBufferNum)
		, m_graphicsPipeLineState(initParam.graphicsPipeLineNum, initParam.rootSignatureNum)
		, m_descriptorHeap(initParam.basicDescriptorHeapNum, initParam.rtvDescriptorHeapNum, initParam.textureBufferNum, initParam.constantBufferNum, initParam.renderTargetBufferNum, initParam.backBufferNum)
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

		// �R�}���h�A���P�[�^�����
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

		// �R�}���h���X�g�����
		m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

		// �R�}���h�L���[�����
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		
		// �X���b�v�`�F�[�������
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

		// �t�F���X������������
		m_fence.initialize(m_device);

		// ���񃊃Z�b�g
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// �r���[�|�[�g�����
		m_viewport.create(0, { { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// �V�U�[��`�����
		m_scissorRect.create(0, { { tktkMath::vec2Zero, windowSize } });

		// �X���b�v�`�F�[���̃o�b�N�o�b�t�@�[���f�B�X�N���v�^�q�[�v�Ŏg�����߂̏���
		for (unsigned int i = 0; i < 2U; ++i)
		{
			m_descriptorHeap.createBackBuffer(i, m_swapChain, i);
		}

		// �o�b�N�o�b�t�@�[�p�̃f�B�X�N���v�^�q�[�v�����
		{
			RtvDescriptorHeapInitParam initParam{};
			initParam.m_shaderVisible = false;
			initParam.m_descriptorParamArray.resize(2U);
			initParam.m_descriptorParamArray.at(0U).m_type = RtvDescriptorType::backBuffer;
			initParam.m_descriptorParamArray.at(0U).m_id = 0U;
			initParam.m_descriptorParamArray.at(1U).m_type = RtvDescriptorType::backBuffer;
			initParam.m_descriptorParamArray.at(1U).m_id = 1U;

			m_descriptorHeap.createRtvDescriptorHeap(0, m_device, initParam);
		}

		// �`�悷�钸�_�̔z��
		std::vector<VertexData> vertices =
		{
			{{ -0.4f, -0.7f, 0.0f }, { 0.0f, 1.0f}},
			{{ -0.4f,  0.7f, 0.0f }, { 0.0f, 0.0f}},
			{{  0.4f, -0.7f, 0.0f }, { 1.0f, 1.0f}},
			{{  0.4f,  0.7f, 0.0f }, { 1.0f, 0.0f}}
		};
		m_vertexBuffer.create(0, m_device, vertices);

		// �`�悷�钸�_�̃C���f�b�N�X
		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			2, 1, 3
		};
		m_indexBuffer.create(0, m_device, indices);

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

			m_graphicsPipeLineState.createRootSignature(0, m_device, initParam);
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

			m_graphicsPipeLineState.createGraphicsPipeLineState(
				0,
				m_device,
				initParam,
				"res/BasicVertexShader.cso",
				"res/BasicPixelShader.cso",
				0
				);
		}

		// �e�N�X�`���o�b�t�@�����
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format				= DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize			= 1U;
			formatParam.mipLevels			= 1U;
			formatParam.sampleDescCount		= 1U;
			formatParam.sampleDescQuality	= 0U;

			m_descriptorHeap.gpuPriorityLoadTextureBuffer(0, m_device, m_commandList, formatParam, "res/test.png");

			// �R�}���h���X�g�����
			m_commandList->Close();

			// �R�}���h���X�g�����s����
			ID3D12CommandList* commandLists[] = { m_commandList };
			m_commandQueue->ExecuteCommandLists(1, commandLists);

			// GPU�������I���܂ő҂�
			m_fence.waitGpuProcess(m_commandQueue);

			// �R�}���h�A���P�[�^�����Z�b�g����
			m_commandAllocator->Reset();

			// �R�}���h���X�g�����Z�b�g����
			m_commandList->Reset(m_commandAllocator, nullptr);
		}

		// �萔�o�b�t�@�����
		{
			tktkMath::Matrix4 mat = tktkMath::mat4Identity;
			m_descriptorHeap.createConstantBuffer(0, m_device, mat);
		}

		// �f�B�X�N���v�^�q�[�v�����
		{
			BasicDescriptorHeapInitParam initParam{};
			initParam.m_shaderVisible = true;
			initParam.m_descriptorParamArray.resize(2U);
			initParam.m_descriptorParamArray.at(0U).m_type = BasicDescriptorType::textureBuffer;
			initParam.m_descriptorParamArray.at(0U).m_id = 0U;
			initParam.m_descriptorParamArray.at(1U).m_type = BasicDescriptorType::constantBuffer;
			initParam.m_descriptorParamArray.at(1U).m_id = 0U;

			m_descriptorHeap.createBasicDescriptorHeap(0U, m_device, initParam);
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
		// ���݂̃o�b�N�o�b�t�@�[�̃C���f�b�N�X���擾����
		m_curBackBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();

		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		m_descriptorHeap.useBackBuffer(m_curBackBufferIndex, m_commandList);

		// ���݂̃o�b�N�o�b�t�@�[��`���ɐݒ肷��
		m_descriptorHeap.setRenderTarget(0, m_device, m_commandList, m_curBackBufferIndex, 1U);

		// ���݂̃o�b�N�o�b�t�@�[���w�肵���P�F�œh��Ԃ�
		tktkMath::Color clearColor = { 1.0f, 1.0f, 0.0f, 1.0f };
		m_descriptorHeap.clearRenderTarget(0U, m_device, m_commandList, m_curBackBufferIndex, clearColor);
		
		// �O���t�B�b�N�p�C�v���C���X�e�[�g��ݒ肷��
		m_graphicsPipeLineState.set(0, m_commandList);
		
		// �O���t�B�b�N�p�C�v���C���Ƀf�B�X�N���v�^�q�[�v��ݒ肷��
		m_descriptorHeap.set(m_device, m_commandList, { { DescriptorHeapType::basic, 0U } });

		// �g���C�A���O�����X�g�ŕ`�悷��悤�ɐݒ肷��
		m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// ���_�o�b�t�@����ݒ肷��
		m_vertexBuffer.set(0, m_commandList);
		
		// �C���f�b�N�X�o�b�t�@����ݒ肷��
		m_indexBuffer.set(0, m_commandList);
		
		// �r���[�|�[�g��ݒ肷��
		m_viewport.set(0, m_commandList);
		
		// �V�U�[��`��ݒ肷��
		m_scissorRect.set(0, m_commandList);
		
		// �`��
		m_commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	}

	void DX3DBaseObjects::endDraw()
	{
		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		m_descriptorHeap.unUseBackBuffer(m_curBackBufferIndex, m_commandList);

		// �R�}���h���X�g�����
		m_commandList->Close();

		// �R�}���h���X�g���R�}���h�L���[�ɓn��
		std::array<ID3D12CommandList*, commandListCount> commandLists = { m_commandList };
		m_commandQueue->ExecuteCommandLists(commandListCount, commandLists.data());

		// GPU�������I���܂ő҂�
		m_fence.waitGpuProcess(m_commandQueue);

		// �R�}���h�A���P�[�^�����Z�b�g����
		m_commandAllocator->Reset();

		// �R�}���h���X�g�����Z�b�g����
		m_commandList->Reset(m_commandAllocator, nullptr);
		
		// ��ʂ��t���b�v����
		m_swapChain->Present(1, 0);
	}
}