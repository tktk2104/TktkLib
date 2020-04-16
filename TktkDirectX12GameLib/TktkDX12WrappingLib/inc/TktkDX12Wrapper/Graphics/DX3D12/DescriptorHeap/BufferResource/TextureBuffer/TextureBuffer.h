#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <array>
#include <TktkFileIo/lodepng.h>
#include "TextureBufferData.h"

namespace tktk
{
	template <int TextureBufferNum>
	class TextureBuffer
	{
	public:

		TextureBuffer() = default;

	public:
		
		void cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void cpuPriorityLoad(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		void gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);
	
		void createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
		
	private:

		std::array<TextureBufferData, TextureBufferNum> m_textureBufferDataArray{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<int TextureBufferNum>
	inline void TextureBuffer<TextureBufferNum>::cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.at(id).cpuPriorityInitialize(device, formatParam, dataParam);
	}

	template<int TextureBufferNum>
	inline void TextureBuffer<TextureBufferNum>::gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.at(id).gpuPriorityInitialize(device, commandList, formatParam, dataParam);
	}

	template<int TextureBufferNum>
	inline void TextureBuffer<TextureBufferNum>::cpuPriorityLoad(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		TexBuffData dataParam{};
		auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
		if (error != 0)
		{
			throw std::runtime_error("can not open " + texDataPath);
		}
		cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	template<int TextureBufferNum>
	inline void TextureBuffer<TextureBufferNum>::gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		TexBuffData dataParam{};
		auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
		if (error != 0)
		{
			throw std::runtime_error("can not open " + texDataPath);
		}
		gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	template<int TextureBufferNum>
	inline void TextureBuffer<TextureBufferNum>::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_textureBufferDataArray.at(id).createShaderResourceView(device, heapHandle);
	}
}
#endif // !TEXTURE_BUFFER_H_