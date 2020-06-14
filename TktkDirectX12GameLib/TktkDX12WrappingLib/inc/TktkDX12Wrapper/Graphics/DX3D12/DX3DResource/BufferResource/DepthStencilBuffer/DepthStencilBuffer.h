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

		void create(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		void use(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void unUse(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void allUse(ID3D12GraphicsCommandList* commandList);

		void allUnUse(ID3D12GraphicsCommandList* commandList);

		void createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		const tktkMath::Vector2& getDepthStencilSize(unsigned int id) const;

	private:

		HeapArray<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
