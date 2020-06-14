#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/DX3DResource.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	DX3DResource::DX3DResource(DX3DResourceInitParam initParam)
		: m_sysResIdGetter(&initParam)	// <=【※ここの初期化時に「initParam」の値にデフォルトのリソースの数が足されます】
		, m_viewport(initParam.viewPortNum)
		, m_scissorRect(initParam.scissorRectNum)
		, m_graphicsPipeLine(initParam.pipeLineStateNum, initParam.rootSignatureNum)
		, m_descriptorHeap(initParam.descriptorHeapInitParam)
		, m_bufferResource(initParam.bufferResourceInitParam)
	{
	}

	void DX3DResource::createViewport(unsigned int id, const std::vector<ViewportInitParam>& initParamArray)
	{
		m_viewport.create(id, initParamArray);
	}

	void DX3DResource::createScissorRect(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray)
	{
		m_scissorRect.create(id, initParamArray);
	}

	void DX3DResource::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_graphicsPipeLine.createRootSignature(id, device, initParam);
	}

	void DX3DResource::createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		m_graphicsPipeLine.createPipeLineState(id, device, initParam, shaderFilePath);
	}

	void DX3DResource::createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_bufferResource.createVertexBuffer(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX3DResource::createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indices)
	{
		m_bufferResource.createIndexBuffer(id, device, indices);
	}

	void DX3DResource::createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.createConstantBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::createRenderTargetBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		m_bufferResource.createRenderTargetBuffer(id, device, renderTargetSize, clearColor);
	}

	void DX3DResource::createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_bufferResource.createRenderTargetBuffer(id, swapChain, backBufferIndex);
	}

	void DX3DResource::createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		m_bufferResource.createDepthStencilBuffer(id, device, initParam);
	}

	void DX3DResource::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_bufferResource.cpuPriorityCreateTextureBuffer(id, device, formatParam, dataParam);
	}

	void DX3DResource::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_bufferResource.gpuPriorityCreateTextureBuffer(id, device, commandList, formatParam, dataParam);
	}

	void DX3DResource::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath)
	{
		m_bufferResource.cpuPriorityLoadTextureBuffer(id, device, texDataPath);
	}

	void DX3DResource::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		m_bufferResource.gpuPriorityLoadTextureBuffer(id, device, commandList, texDataPath);
	}

	void DX3DResource::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createBasicDescriptorHeap(id, device, initParam);

		// 全てのディスクリプタの先頭アドレスの配列を取得する
		auto cpuHeapHandleArray = m_descriptorHeap.getCpuBasicHeapHandleArray(id, device);

		// 設定しているディスクリプタの番号
		unsigned int curDescriptorIndex = 0U;

		for (const auto& descriptorParam : initParam.descriptorTableParamArray)
		{
			for (const auto& node : descriptorParam.descriptorParamArray)
			{
				switch (descriptorParam.type)
				{
				case BasicDescriptorType::constantBuffer:

					createBasicDescriptorCbufferView(device, cpuHeapHandleArray.at(curDescriptorIndex), node);
					break;

				case BasicDescriptorType::textureBuffer:

					createBasicDescriptorShaderResourceView(device, cpuHeapHandleArray.at(curDescriptorIndex), node);
					break;
				}

				curDescriptorIndex++;
			}
		}

		/*for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			const auto& descriptorParam = initParam.descriptorParamArray.at(i);

			switch (descriptorParam.type)
			{
			case BasicDescriptorType::constantBuffer:

				createBasicDescriptorCbufferView(device, cpuHeapHandleArray.at(i), descriptorParam.useBufferParamArray);
				break;

			case BasicDescriptorType::textureBuffer:

				createBasicDescriptorShaderResourceView(device, cpuHeapHandleArray.at(i), descriptorParam.useBufferParamArray);
				break;
			}
		}*/
	}

	void DX3DResource::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createRtvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuRtvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case RtvDescriptorType::normal:

				m_bufferResource.createRenderTargetView(initParam.descriptorParamArray.at(i).id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam)
	{
		// バッファを割り当てていないディスクリプタヒープを作る
		m_descriptorHeap.createDsvDescriptorHeap(id, device, initParam);

		auto cpuHeapHandleArray = m_descriptorHeap.getCpuDsvHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.descriptorParamArray.size(); i++)
		{
			switch (initParam.descriptorParamArray.at(i).type)
			{
			case DsvDescriptorType::normal:

				m_bufferResource.createDepthStencilView(initParam.descriptorParamArray.at(i).id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	void DX3DResource::updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_bufferResource.updateConstantBuffer(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void DX3DResource::clearRenderTargetView(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_descriptorHeap.clearRenderTarget(id, device, commandList, rtvLocationIndex, color);
	}

	void DX3DResource::clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.allUseDepthStencilBuffer(commandList);

		m_descriptorHeap.clearDepthStencilViewAll(device, commandList);

		m_bufferResource.allUnUseDepthStencilBuffer(commandList);
	}

	const tktkMath::Vector3& DX3DResource::getTextureBufferSize(unsigned int id) const
	{
		return m_bufferResource.getTextureSize(id);
	}

	const tktkMath::Vector2& DX3DResource::getDepthStencilBufferSize(unsigned int id) const
	{
		return m_bufferResource.getDepthStencilSize(id);
	}

	const tktkMath::Vector2& DX3DResource::getRenderTargetBufferSize(unsigned int id) const
	{
		return m_bufferResource.getRenderTargetSize(id);
	}

	const std::vector<unsigned int>& DX3DResource::getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(id);
	}

	const std::vector<unsigned int>& DX3DResource::getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const
	{
		return m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(id);
	}

	void DX3DResource::setRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.useAsRenderTargetBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRenderTarget(rtvDescriptorHeapId, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		// 使用するレンダーターゲットバッファーを取得して、書き込み状態に設定する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.useAsRenderTargetBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}

		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.useDepthStencilBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「レンダーターゲット用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRenderTargetAndDepthStencil(rtvDescriptorHeapId, dsvDescriptorHeapId, device, commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DResource::setOnlyDepthStencil(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(id);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.useDepthStencilBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setOnlyDepthStencil(id, device, commandList);
	}

	void DX3DResource::setBackBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex)
	{
		// バックバッファはフレームの初めに書き込み状態に設定されているのでそのまま ディスクリプタヒープを設定できる
		m_descriptorHeap.setRenderTarget(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex)
	{
		// 使用する深度ステンシルバッファーを取得して、書き込み状態に設定する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.useDepthStencilBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}

		// 「バックバッファー用のディスクリプタヒープ」と「深度ステンシル用のディスクリプタヒープ」を設定する
		m_descriptorHeap.setRenderTargetAndDepthStencil(getSystemId(SystemRtvDescriptorHeapType::BackBuffer), dsvDescriptorHeapId, device, commandList, backBufferIndex, 1U);
	}

	void DX3DResource::unSetRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount)
	{
		// 使用していたレンダーターゲットバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto rtvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getRtvDescriptorHeapUseBufferIdArray(rtvDescriptorHeapId);
		for (unsigned int i = 0; i < rtvCount; i++)
		{
			m_bufferResource.unUseAsRenderTargetBuffer(rtvDescriptorHeapUseBufferIdArray.at(startRtvLocationIndex + i), commandList);
		}
	}

	void DX3DResource::unSetDepthStencil(unsigned int dsvDescriptorHeapId, ID3D12GraphicsCommandList* commandList)
	{
		// 使用していた深度ステンシルバッファーを取得して、ピクセルシェーダーで使用する状態に変更する
		auto dsvDescriptorHeapUseBufferIdArray = m_descriptorHeap.getDsvDescriptorHeapUseBufferIdArray(dsvDescriptorHeapId);
		for (const auto& dsvDescriptorHeapUseBufferId : dsvDescriptorHeapUseBufferIdArray)
		{
			m_bufferResource.unUseDepthStencilBuffer(dsvDescriptorHeapUseBufferId, commandList);
		}
	}

	void DX3DResource::useAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.useBackBuffer(id, commandList);
	}

	void DX3DResource::unUseAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.unUseBackBuffer(id, commandList);
	}

	void DX3DResource::setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_viewport.set(id, commandList);
	}

	void DX3DResource::setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_scissorRect.set(id, commandList);
	}

	void DX3DResource::setPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_graphicsPipeLine.set(id, commandList);
	}

	void DX3DResource::setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.setVertexBuffer(id, commandList);
	}

	void DX3DResource::setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_bufferResource.setIndexBuffer(id, commandList);
	}

	void DX3DResource::setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		m_descriptorHeap.set(device, commandList, heapParamArray);
	}

	void DX3DResource::createBasicDescriptorCbufferView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam)
	{
#ifdef _DEBUG
		if (useBufferParam.type != BufferType::constant) throw std::runtime_error("useBuffer Type Error -not cbuffer-");
#endif // _DEBUG

		m_bufferResource.createConstantBufferView(useBufferParam.id, device, cpuHandle);
	}

	void DX3DResource::createBasicDescriptorShaderResourceView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam)
	{
		switch (useBufferParam.type)
		{
		case BufferType::texture:

			m_bufferResource.createShaderResourceView(useBufferParam.id, device, cpuHandle);
			break;

		case BufferType::renderTarget:

			m_bufferResource.createRtvShaderResourceView(useBufferParam.id, device, cpuHandle);
			break;

		case BufferType::depthStencil:

			m_bufferResource.createDsvShaderResourceView(useBufferParam.id, device, cpuHandle);
			break;

		default:
#ifdef _DEBUG
			throw std::runtime_error("useBuffer Type Error -not ShaderResourceView-");
#endif // _DEBUG
			break;
		}
	}
}