#ifndef TEXTURE_BUFFER_DATA_H_
#define TEXTURE_BUFFER_DATA_H_

#include <d3d12.h>
#include "TextureBufferInitParam.h"
#include "ShaderResourceViewInitParam.h"

namespace tktk
{
	class TextureBufferData
	{
	public:

		TextureBufferData() = default;
		~TextureBufferData();

	public:

		void cpuPriorityInitialize(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void gpuPriorityInitialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void createShaderResource(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	private:

		ShaderResourceViewInitParam	m_srvInitParam{};
		ID3D12Resource*				m_textureBuffer{ nullptr };
		ID3D12Resource*				m_uploadBuff{ nullptr };
	};
}
#endif // !TEXTURE_BUFFER_DATA_H_