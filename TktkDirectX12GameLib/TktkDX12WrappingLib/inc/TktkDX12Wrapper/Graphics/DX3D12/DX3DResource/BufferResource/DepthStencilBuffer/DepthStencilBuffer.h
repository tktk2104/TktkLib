#ifndef DEPTH_STENCIL_BUFFER_H_
#define DEPTH_STENCIL_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DepthStencilBufferData.h"

namespace tktk
{
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(unsigned int depthStencilBufferNum);

	public:

		void create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);

		void createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		HeapArray<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
