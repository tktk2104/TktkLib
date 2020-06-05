#ifndef RENDER_TARGET_BUFFER_DATA_H_
#define RENDER_TARGET_BUFFER_DATA_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class RenderTargetBufferData
	{
	public:

		RenderTargetBufferData(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		RenderTargetBufferData(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);
		~RenderTargetBufferData();

	public:

		D3D12_RESOURCE_BARRIER createBarrierDesc(D3D12_RESOURCE_STATES beforState, D3D12_RESOURCE_STATES afterState) const;

		void createRenderTargetView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void createShaderResourceView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		ID3D12Resource* m_renderTargetBuffer{ nullptr };
		bool			m_mustRelease{ true };
	};
}
#endif // !RENDER_TARGET_BUFFER_DATA_H_