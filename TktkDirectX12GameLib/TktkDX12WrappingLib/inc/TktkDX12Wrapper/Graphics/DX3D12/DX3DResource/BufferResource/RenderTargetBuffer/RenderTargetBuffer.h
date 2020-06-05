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

		void create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		void create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void useAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUseAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void useAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUseAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void createRenderTargetView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		HeapArray<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_