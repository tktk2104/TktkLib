#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector3.h>

#include <stdexcept>
#include <vector>

namespace tktk
{
	constexpr unsigned int commandListCount{ 1 };

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

		// �f�o�C�X�����
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));

		// �t�@�N�g�������
		CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));

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

		// �R�}���h�A���P�[�^�����Z�b�g����
		m_commandAllocator->Reset();

		// �`�悷�钸�_�̔z��
		tktkMath::Vector3 vertices[] =
		{
			{ -1.0f, -1.0f, 0.0f },
			{ -1.0f,  1.0f, 0.0f },
			{  1.0f, -1.0f, 0.0f }
		};

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

		ID3D12Resource* vertexBuffer{ nullptr };
		m_device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertexBuffer)
		);

		tktkMath::Vector3* vertMap{ nullptr };

		vertexBuffer->Map(0, nullptr, (void**)(&vertMap));
		std::copy(std::begin(vertices), std::end(vertices), vertMap);
		vertexBuffer->Unmap(0, nullptr);

		m_vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = sizeof(vertices);
		m_vertexBufferView.StrideInBytes = sizeof(vertices[0]);

		ID3DBlob* vsBlob{ nullptr };
		ID3DBlob* psBlob{ nullptr };

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

		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* rootSigBlob{ nullptr };
		ID3DBlob* errorBlob{ nullptr };
		D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);

		
		m_device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature));

		rootSigBlob->Release();

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
	
		//// �����_�����O�p�C�v���C���X�e�[�g��ݒ肷��
		//m_commandList->SetPipelineState(m_pipeLineState);

		//// �O���t�B�b�N�p�C�v���C���Ƀ��[�g�V�O�l�`����ݒ肷��
		//m_commandList->SetGraphicsRootSignature(m_rootSignature);

		//// �g���C�A���O�����X�g�ŕ`�悷��悤�ɐݒ肷��
		//m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//
		//// ���_�o�b�t�@����ݒ肷��
		//m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);

		//// �`��
		//m_commandList->DrawInstanced(3, 1, 0, 0);
	}

	void DX3DBaseObjects::endDraw()
	{
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

		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�r���[�̃��\�[�X�o���A����������
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_backBuffers.at(m_curBackBufferIndex);
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		m_commandList->ResourceBarrier(1, &barrierDesc);

		// ��ʂ��t���b�v����
		m_swapChain->Present(1, 0);
	}
}