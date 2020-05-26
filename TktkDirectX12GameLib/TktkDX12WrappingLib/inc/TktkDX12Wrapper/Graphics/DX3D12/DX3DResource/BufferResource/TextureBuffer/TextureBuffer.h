#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
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
		
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	private:

		HeapArray<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_