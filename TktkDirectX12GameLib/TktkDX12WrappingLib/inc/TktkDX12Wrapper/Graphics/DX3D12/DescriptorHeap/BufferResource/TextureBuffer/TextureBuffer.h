#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <vector>
#include "TextureBufferData.h"

namespace tktk
{
	class TextureBuffer
	{
	public:

		TextureBuffer(unsigned int textureBufferNum);

	public:
		
		void cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void cpuPriorityLoad(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		void gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);
	
		void createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
		
	private:

		std::vector<TextureBufferData> m_textureBufferDataArray{};
	};
}
#endif // !TEXTURE_BUFFER_H_