#include "TktkDX12Wrapper/Graphics/DX3D12/DescriptorHeap/BufferResource/TextureBuffer/TextureBuffer.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include <TktkFileIo/lodepng.h>

namespace tktk
{
	TextureBuffer::TextureBuffer(unsigned int textureBufferNum)
	{
		m_textureBufferDataArray.resize(textureBufferNum);
	}

	void TextureBuffer::cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.at(id).cpuPriorityInitialize(device, formatParam, dataParam);
	}

	void TextureBuffer::gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.at(id).gpuPriorityInitialize(device, commandList, formatParam, dataParam);
	}

	void TextureBuffer::cpuPriorityLoad(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		TexBuffData dataParam{};
		auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
		if (error != 0)
		{
			throw std::runtime_error("can not open " + texDataPath);
		}
#endif // _DEBUG
		cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	void TextureBuffer::gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		TexBuffData dataParam{};
		auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
		if (error != 0)
		{
			throw std::runtime_error("can not open " + texDataPath);
		}
#endif // _DEBUG
		gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	void TextureBuffer::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_textureBufferDataArray.at(id).createShaderResourceView(device, heapHandle);
	}
}