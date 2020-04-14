#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <array>
#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "../../Window/Window.h"

#include "../VertexBuffer/VertexBuffer.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../GraphicsPipeLineState/GraphicsPipeLineState.h"

namespace tktk
{
	constexpr unsigned int backBufferCount{ 2 };

	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(HWND hwnd, const tktkMath::Vector2& windowSize);
		~DX3DBaseObjects();

	public:

		void beginDraw();
		void endDraw();

	public:



	private:

		D3D12_VIEWPORT									m_viewport							{};
		D3D12_RECT										m_scissorrect						{};
		ID3D12DescriptorHeap*							m_basicDescHeap						{ nullptr };

		ID3D12Device*									m_device							{ nullptr };
		IDXGIFactory6*									m_factory							{ nullptr };
		ID3D12CommandAllocator*							m_commandAllocator					{ nullptr };
		ID3D12GraphicsCommandList*						m_commandList						{ nullptr };
		ID3D12Fence*									m_fence								{ nullptr };
		unsigned int									m_fenceVal							{ 0U };
		ID3D12CommandQueue*								m_commandQueue						{ nullptr };
		IDXGISwapChain1*								m_swapChain							{ nullptr };
		ID3D12DescriptorHeap*							m_backBufferRenderTargetViewHeap	{ nullptr };
		std::array<ID3D12Resource*, backBufferCount>	m_backBuffers						{};
		unsigned int									m_curBackBufferIndex				{ 0U };

		VertexBuffer<1>					m_vertexBuffer{};
		IndexBuffer<1>					m_indexBuffer{};
		GraphicsPipeLineState<1, 1>		m_graphicsPipeLineState{};
	};
}
#endif // !DX3D_BASE_OBJECTS_H_