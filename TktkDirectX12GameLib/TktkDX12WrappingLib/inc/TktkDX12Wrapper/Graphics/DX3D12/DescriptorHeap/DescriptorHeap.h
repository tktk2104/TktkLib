#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include <array>
#include "DescriptorHeapData.h"
#include "../BufferResource/TextureBuffer/TextureBuffer.h"
#include "../BufferResource/ConstantBuffer/ConstantBuffer.h"

namespace tktk
{
	template <int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	class DescriptorHeap
	{
	public:

		DescriptorHeap() = default;

	public:

		void createDescriptorHeap(unsigned int id, ID3D12Device* device, const std::vector<DescriptorHeapInitParam>& initParamArray);

		void set(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public:

		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public:

		template <class ConstantBufferDataType>
		void createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);

	private:

		TextureBuffer<TextureBufferNum>						m_textureBuffer{};
		ConstantBuffer<ConstantBufferNum>					m_constantBuffer{};
		std::array<DescriptorHeapData, DescriptorHeapNum>	m_descriptorHeapDataArray{};
	};

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::createDescriptorHeap(unsigned int id, ID3D12Device* device, const std::vector<DescriptorHeapInitParam>& initParamArray)
	{
		m_descriptorHeapDataArray.at(id).initialize(device, initParamArray);

		for (unsigned int i = 0; i < initParamArray.size(); i++)
		{
			auto cpuHeapHandleArray = m_descriptorHeapDataArray.at(id).getCpuHeapHandleArray(i);

			for (unsigned int j = 0; j < initParamArray.at(i).m_descriptorParamArray.size(); j++)
			{
				switch (initParamArray.at(i).m_descriptorParamArray.at(j).descriptorType)
				{
				case DescriptorType::constantBuffer:

					m_constantBuffer.createShaderResource(initParamArray.at(i).m_descriptorParamArray.at(j).descriptorIndex, device, cpuHeapHandleArray.at(j));
					break;

				case DescriptorType::textureBuffer:

					m_textureBuffer.createShaderResource(initParamArray.at(i).m_descriptorParamArray.at(j).descriptorIndex, device, cpuHeapHandleArray.at(j));
					break;
				}
			}
		}
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::set(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_descriptorHeapDataArray.at(id).set(commandList);
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.cpuPriorityLoad(id, device, formatParam, texDataPath);
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.gpuPriorityLoad(id, device, commandList, formatParam, texDataPath);
	}

	template<int DescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum>
	template<class ConstantBufferDataType>
	inline void DescriptorHeap<DescriptorHeapNum, TextureBufferNum, ConstantBufferNum>::createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		m_constantBuffer.create(id, device, rawConstantBufferData);
	}
}
#endif // !DESCRIPTOR_HEAP_H_
