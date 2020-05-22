#include "TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor)
		: m_dX3DResource(initParam.resourceInitParam)
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
		m_dX3DResource.createViewport(0, { { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// �V�U�[��`�����
		m_dX3DResource.createScissorRect(0, { { tktkMath::vec2Zero, windowSize } });

		// �X���b�v�`�F�[���̃o�b�N�o�b�t�@�[���f�B�X�N���v�^�q�[�v�Ŏg�����߂̏���
		for (unsigned int i = 0; i < 2U; ++i)
		{
			m_dX3DResource.createBackBuffer(i, m_swapChain, i);
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

			m_dX3DResource.createRtvDescriptorHeap(0U, m_device, initParam);
		}

		// �f�t�H���g�̐[�x�o�b�t�@�[�Ɛ[�x�f�B�X�N���v�^�q�[�v���������
		{
			m_dX3DResource.createDepthStencilBuffer(0U, m_device, windowSize);

			DsvDescriptorHeapInitParam initParam{};
			initParam.m_shaderVisible = false;
			initParam.m_descriptorParamArray.push_back({ DsvDescriptorType::normal, 0U });

			m_dX3DResource.createDsvDescriptorHeap(0U, m_device, initParam);
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
		m_dX3DResource.useBackBuffer(m_curBackBufferIndex, m_commandList);

		// ���݂̃o�b�N�o�b�t�@�[��`���ɐݒ肷��
		setBackBufferRenderTarget();

		// ���݂̃o�b�N�o�b�t�@�[���w�肵���P�F�œh��Ԃ�
		m_dX3DResource.clearRenderTarget(0U, m_device, m_commandList, m_curBackBufferIndex, m_backGroundColor);
		
		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		m_dX3DResource.clearDepthStencilViewAll(m_device, m_commandList);

		// �r���[�|�[�g��ݒ肷��
		m_dX3DResource.setViewport(0, m_commandList);
		
		// �V�U�[��`��ݒ肷��
		m_dX3DResource.setScissorRect(0, m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		m_dX3DResource.unUseBackBuffer(m_curBackBufferIndex, m_commandList);

		// �R�}���h���X�g�����s����
		executeCommandList();

		// ��ʂ��t���b�v����
		m_swapChain->Present(1, 0);
	}

	void DX3DBaseObjects::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dX3DResource.createRootSignature(id, m_device, initParam);
	}

	void DX3DBaseObjects::createGraphicsPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dX3DResource.createGraphicsPipeLineState(id, m_device, initParam, shaderFilePath);
	}

	void DX3DBaseObjects::createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dX3DResource.createVertexBuffer(id, m_device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DBaseObjects::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dX3DResource.createIndexBuffer(id, m_device, indices);
	}

	void DX3DBaseObjects::createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.createConstantBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize)
	{
		m_dX3DResource.createDepthStencilBuffer(id, m_device, depthStencilSize);
	}

	void DX3DBaseObjects::createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createBasicDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam)
	{
		m_dX3DResource.createDsvDescriptorHeap(id, m_device, initParam);
	}

	void DX3DBaseObjects::gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_dX3DResource.gpuPriorityLoadTextureBuffer(id, m_device, m_commandList, formatParam, texDataPath);
	}

	void DX3DBaseObjects::updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.updateConstantBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureSize(unsigned int id) const
	{
		return m_dX3DResource.getTextureSize(id);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::setBackBufferRenderTarget()
	{
		m_dX3DResource.setBackBufferRenderTarget(m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::setUseDepthStencilBackBufferRenderTarget(unsigned int dsvDescriptorHeapId)
	{
		m_dX3DResource.setUseDepthStencilBackBufferRenderTarget(dsvDescriptorHeapId, m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::setViewport(unsigned int id)
	{
		m_dX3DResource.setViewport(id, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(unsigned int id)
	{
		m_dX3DResource.setScissorRect(id, m_commandList);
	}

	void DX3DBaseObjects::setGraphicsPipeLineState(unsigned int id)
	{
		m_dX3DResource.setGraphicsPipeLineState(id, m_commandList);
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
}