#ifndef DEPTH_STENCIL_BUFFER_DATA_H_
#define DEPTH_STENCIL_BUFFER_DATA_H_

#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "DepthStencilBufferInitParam.h"

namespace tktk
{
	class DepthStencilBufferData
	{
	public:

		DepthStencilBufferData(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);
		~DepthStencilBufferData() = default;

	public:

		void use(ID3D12GraphicsCommandList* commandList);

		void unUse(ID3D12GraphicsCommandList* commandList);

		void createDepthStencilView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void createShaderResourceView(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		const tktkMath::Vector2& getDepthStencilSize() const;

	private:

		bool				m_useAsShaderResource;
		tktkMath::Vector2	m_depthStencilSize;
		ID3D12Resource*		m_depthStencilBuffer{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_BUFFER_DATA_H_