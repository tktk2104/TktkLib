#ifndef DEPTH_STENCIL_BUFFER_DATA_H_
#define DEPTH_STENCIL_BUFFER_DATA_H_

#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class DepthStencilBufferData
	{
	public:

		DepthStencilBufferData(ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);
		~DepthStencilBufferData() = default;

	public:

		void createDepthStencilView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		ID3D12Resource* m_depthStencilBuffer{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_BUFFER_DATA_H_