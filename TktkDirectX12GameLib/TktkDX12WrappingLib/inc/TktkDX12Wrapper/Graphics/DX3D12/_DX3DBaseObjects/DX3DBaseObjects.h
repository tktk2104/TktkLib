#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <vector>
#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "DX3DBaseObjectsInitParam.h"

#include "../Fence/Fence.h"
#include "../Viewport/Viewport.h"
#include "../ScissorRect/ScissorRect.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../GraphicsPipeLineState/GraphicsPipeLineState.h"
#include "../DescriptorHeap/DescriptorHeap.h"

namespace tktk
{
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize);
		~DX3DBaseObjects();

	public:

		void beginDraw();
		void endDraw();

		void executeCommandList();

	public:

		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		void createGraphicsPipeLineState(unsigned int graphicsPipeLineId, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId);

		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		void createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public:



	private:

		ID3D12Device*				m_device				{ nullptr };
		IDXGIFactory6*				m_factory				{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList			{ nullptr };
		ID3D12CommandQueue*			m_commandQueue			{ nullptr };
		IDXGISwapChain1*			m_swapChain				{ nullptr };
		unsigned int				m_curBackBufferIndex	{ 0U };
		Fence						m_fence					{};
		Viewport					m_viewport;
		ScissorRect					m_scissorRect;
		VertexBuffer				m_vertexBuffer;
		IndexBuffer					m_indexBuffer;
		GraphicsPipeLineState		m_graphicsPipeLineState;
		DescriptorHeap				m_descriptorHeap;
	};
}
#endif // !DX3D_BASE_OBJECTS_H_