#include "TktkDX12Wrapper/Graphics/DX3D12/DX3DResource/BufferResource/TextureBuffer/TextureBuffer.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include <TktkFileIo/BinaryFileReader.h>
#include <TktkFileIo/lodepng.h>
#include <TktkFileIo/lodebmp.h>


namespace tktk
{
	TextureBuffer::TextureBuffer(unsigned int textureBufferNum)
		: m_textureBufferDataArray(textureBufferNum)
	{
	}

	void TextureBuffer::cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.emplaceAt(id, device, formatParam, dataParam);
	}

	void TextureBuffer::gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBufferDataArray.emplaceAt(id, device, commandList, formatParam, dataParam);
	}

	void TextureBuffer::cpuPriorityLoad(unsigned int id, ID3D12Device* device, const std::string& texDataPath)
	{
		TexBufFormatParam formatParam{};
		TexBuffData dataParam{};

		auto extension = texDataPath.substr(texDataPath.size() - 3U, 3U);

		if (extension == "bmp")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			lodebmp::loadData outData{};
			lodebmp::load(&outData, texDataPath);
			dataParam.width = outData.width;
			dataParam.height = outData.height;
			dataParam.textureData.resize(outData.data.size());
			std::copy(std::begin(outData.data), std::end(outData.data), std::begin(dataParam.textureData));
		}
		else if (extension == "png")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
			if (error != 0)
			{
				throw std::runtime_error("can not open " + texDataPath);
			}
#endif // _DEBUG
		}
		cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	void TextureBuffer::gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath)
	{
		TexBufFormatParam formatParam{};
		TexBuffData dataParam{};

		auto extension = texDataPath.substr(texDataPath.size() - 3U, 3U);

		if (extension == "bmp")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			lodebmp::loadData outData{};
			lodebmp::load(&outData, texDataPath);
			dataParam.width = outData.width;
			dataParam.height = outData.height;
			dataParam.textureData.resize(outData.data.size());
			std::copy(std::begin(outData.data), std::end(outData.data), std::begin(dataParam.textureData));
		}
		else if (extension == "png")
		{
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			auto error = lodepng::decode(dataParam.textureData, dataParam.width, dataParam.height, texDataPath.c_str());
#ifdef _DEBUG
			if (error != 0)
			{
				throw std::runtime_error("can not open " + texDataPath);
			}
#endif // _DEBUG
		}
		gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	void TextureBuffer::createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle)
	{
		m_textureBufferDataArray.at(id)->createShaderResourceView(device, heapHandle);
	}

	const tktkMath::Vector3& TextureBuffer::getTextureSize(unsigned int id) const
	{
		return m_textureBufferDataArray.at(id)->getTextureSize();
	}
}