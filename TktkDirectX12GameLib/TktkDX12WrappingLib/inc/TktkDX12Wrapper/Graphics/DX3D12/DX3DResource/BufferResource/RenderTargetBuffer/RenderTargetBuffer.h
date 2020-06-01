#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	class RenderTargetBuffer
	{
	public:

		RenderTargetBuffer(unsigned int renderTargetBufferNum);

	public:

		void create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void use(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUse(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void createView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		HeapArray<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_