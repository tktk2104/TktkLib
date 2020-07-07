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
		m_dX3DResource.createViewport(getSystemId(SystemViewportType::Basic), { { windowSize, tktkMath::vec2Zero, 1.0f, 0.0f } });

		// �V�U�[��`�����
		m_dX3DResource.createScissorRect(getSystemId(SystemScissorRectType::Basic), { { tktkMath::vec2Zero, windowSize } });

		// �X���b�v�`�F�[���̃o�b�N�o�b�t�@�[���f�B�X�N���v�^�q�[�v�Ŏg�����߂̏���
		m_dX3DResource.createRtBuffer(getSystemId(SystemRenderTargetBufferType::BackBuffer_1), m_swapChain, 0U);
		m_dX3DResource.createRtBuffer(getSystemId(SystemRenderTargetBufferType::BackBuffer_2), m_swapChain, 1U);

		// �o�b�N�o�b�t�@�[�p�̃f�B�X�N���v�^�q�[�v�����
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

		// �f�t�H���g�̐[�x�o�b�t�@�[�����
		{
			DepthStencilBufferInitParam initParam{};
			initParam.depthStencilSize = windowSize;
			initParam.useAsShaderResource = false;

			m_dX3DResource.createDsBuffer(getSystemId(SystemDepthStencilBufferType::Basic), m_device, initParam);
		}

		// �f�t�H���g�̐[�x�f�B�X�N���v�^�q�[�v�����
		{
			DsvDescriptorHeapInitParam initParam{};
			initParam.shaderVisible = false;
			initParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemId(SystemDepthStencilBufferType::Basic) });

			m_dX3DResource.createDsvDescriptorHeap(getSystemId(SystemDsvDescriptorHeapType::Basic), m_device, initParam);
		}

		// ���e�N�X�`�������
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
		// ���݂̃o�b�N�o�b�t�@�[�̃C���f�b�N�X���擾����
		m_curBackBufferIndex = static_cast<IDXGISwapChain3*>(m_swapChain)->GetCurrentBackBufferIndex();
		
		// ���݂̃o�b�N�o�b�t�@�[�̎�ނ��um_curBackBufferIndex�v���狁�߂�
		auto curBackBufferType = (m_curBackBufferIndex == 0) ? SystemRenderTargetBufferType::BackBuffer_1 : SystemRenderTargetBufferType::BackBuffer_2;
		
		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		m_dX3DResource.beginWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// ���݂̃o�b�N�o�b�t�@�[����`���ɐݒ肷��
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_curBackBufferIndex);

		// ���݂̃o�b�N�o�b�t�@�[���w�肵���P�F�œh��Ԃ�
		m_dX3DResource.clearRtv(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), m_device, m_commandList, m_curBackBufferIndex, m_backGroundColor);
		
		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		m_dX3DResource.clearDsvAll(m_device, m_commandList);

		// �r���[�|�[�g��ݒ肷��
		m_dX3DResource.setViewport(getSystemId(SystemViewportType::Basic), m_commandList);
		
		// �V�U�[��`��ݒ肷��
		m_dX3DResource.setScissorRect(getSystemId(SystemScissorRectType::Basic), m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// ���݂̃o�b�N�o�b�t�@�[�̎�ނ��um_curBackBufferIndex�v���狁�߂�
		auto curBackBufferType = (m_curBackBufferIndex == 0) ? SystemRenderTargetBufferType::BackBuffer_1 : SystemRenderTargetBufferType::BackBuffer_2;
		
		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		m_dX3DResource.endWriteBackBuffer(getSystemId(curBackBufferType), m_commandList);

		// �R�}���h���X�g�����s����
		executeCommandList();

		// ��ʂ��t���b�v����
		m_swapChain->Present(1, 0);
	}

	void DX3DBaseObjects::createRootSignature(unsigned int id, const RootSignatureInitParam& initParam)
	{
		m_dX3DResource.createRootSignature(id, m_device, initParam);
	}

	void DX3DBaseObjects::createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_dX3DResource.createPipeLineState(id, m_device, initParam, shaderFilePath);

		// ����Z�b�g�i���ŏ��ɃZ�b�g�������̂ݏd���������ƂȂ�̂ŁA�쐬����ɐ�s�ŃZ�b�g����j
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

	void DX3DBaseObjects::createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.createCBuffer(id, m_device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::createRenderTargetBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_dX3DResource.createRtBuffer(id, m_device, renderTargetSize, clearColor);
	}

	void DX3DBaseObjects::createDepthStencilBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam)
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

	void DX3DBaseObjects::updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dX3DResource.updateCBuffer(id, m_device, m_commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DBaseObjects::clearRenderTarget(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_dX3DResource.clearRtv(id, m_device, m_commandList, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureSize(unsigned int id) const
	{
		return m_dX3DResource.getTextureBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDepthStencilSize(unsigned int id) const
	{
		return m_dX3DResource.getDsBufferSizePx(id);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRenderTargetSize(unsigned int id) const
	{
		return m_dX3DResource.getRtBufferSizePx(id);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::setRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.setRtv(rtvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.setRtvAndDsv(dsvDescriptorHeapId, dsvDescriptorHeapId, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDepthStencil(unsigned int id)
	{
		m_dX3DResource.setOnlyDsv(id, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBuffer()
	{
		m_dX3DResource.setBackBufferView(m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId)
	{
		m_dX3DResource.setBackBufferViewAndDsv(dsvDescriptorHeapId, m_device, m_commandList, m_curBackBufferIndex);
	}

	void DX3DBaseObjects::unSetRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		m_dX3DResource.unSetRtv(rtvDescriptorHeapId, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDepthStencil(unsigned int dsvDescriptorHeapId)
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

		// �R�s�[���o�b�t�@���폜����
		m_dX3DResource.deleteUploadBufferAll();
	}
}