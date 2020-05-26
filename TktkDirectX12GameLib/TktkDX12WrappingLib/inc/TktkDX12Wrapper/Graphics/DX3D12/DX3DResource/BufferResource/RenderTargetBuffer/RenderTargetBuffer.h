#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	class RenderTargetBuffer
	{
	public:

		RenderTargetBuffer(unsigned int renderTargetBufferNum, unsigned int backBufferNum);

	public:



	public:

		void createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void createBackBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		HeapArray<RenderTargetBufferData>	m_renderTargetBufferDataArray;
		HeapArray<RenderTargetBufferData>	m_backBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_