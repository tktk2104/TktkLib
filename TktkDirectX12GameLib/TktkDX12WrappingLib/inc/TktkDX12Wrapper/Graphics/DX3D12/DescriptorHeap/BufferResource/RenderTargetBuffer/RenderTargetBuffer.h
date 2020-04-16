#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <array>
#include "RenderTargetBufferData.h"

namespace tktk
{
	template <int RenderTargetBufferNum, int BackBufferNum>
	class RenderTargetBuffer
	{
	public:

		RenderTargetBuffer() = default;

	public:



	public:

		void createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void createBackBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		std::array<RenderTargetBufferData, RenderTargetBufferNum>	m_renderTargetBufferDataArray{};
		std::array<RenderTargetBufferData, BackBufferNum>			m_backBufferDataArray{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<int RenderTargetBufferNum, int BackBufferNum>
	inline void RenderTargetBuffer<RenderTargetBufferNum, BackBufferNum>::createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_backBufferDataArray.at(id).initializeBackBuffer(swapChain, backBufferIndex);
	}

	template<int RenderTargetBufferNum, int BackBufferNum>
	inline void RenderTargetBuffer<RenderTargetBufferNum, BackBufferNum>::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_backBufferDataArray.at(id).createBarrierDesc(D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	template<int RenderTargetBufferNum, int BackBufferNum>
	inline void RenderTargetBuffer<RenderTargetBufferNum, BackBufferNum>::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		auto barrierDesc = m_backBufferDataArray.at(id).createBarrierDesc(D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	template<int RenderTargetBufferNum, int BackBufferNum>
	inline void RenderTargetBuffer<RenderTargetBufferNum, BackBufferNum>::createBackBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_backBufferDataArray.at(id).createRenderTargetView(device, heapHandle);
	}
}
#endif // !RENDER_TARGET_BUFFER_H_