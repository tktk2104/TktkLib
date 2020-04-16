#ifndef RENDER_TARGET_BUFFER_DATA_H_
#define RENDER_TARGET_BUFFER_DATA_H_

#include <d3d12.h>
#include <dxgi1_6.h>

namespace tktk
{
	class RenderTargetBufferData
	{
	public:

		RenderTargetBufferData() = default;
		~RenderTargetBufferData();

	public:

		void initializeBackBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		D3D12_RESOURCE_BARRIER createBarrierDesc(D3D12_RESOURCE_STATES beforState, D3D12_RESOURCE_STATES afterState) const;

		void createRenderTargetView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		ID3D12Resource* m_renderTargetBuffer{ nullptr };
		bool			m_mustRelease{ true };
	};
}
#endif // !RENDER_TARGET_BUFFER_DATA_H_