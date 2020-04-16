#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include "DescriptorHeapParam.h"

#include "BasicDescriptorHeap/BasicDescriptorHeap.h"
#include "RtvDescriptorHeap/RtvDescriptorHeap.h"

#include "BufferResource/TextureBuffer/TextureBuffer.h"
#include "BufferResource/ConstantBuffer/ConstantBuffer.h"
#include "BufferResource/RenderTargetBuffer/RenderTargetBuffer.h"

namespace tktk
{
	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	class DescriptorHeap
	{
	public:

		DescriptorHeap() = default;

	public:

		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

		void setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const;
		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

	public:

		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
	
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);
	
	public:
	
		template <class ConstantBufferDataType>
		void createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);

	public:

		void createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);
		void unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		BasicDescriptorHeap<BasicDescriptorHeapNum>					m_basicDescriptorHeap{};
		RtvDescriptorHeap<RtvDescriptorHeapNum>						m_rtvDescriptorHeap{};
		
		TextureBuffer<TextureBufferNum>								m_textureBuffer{};
		ConstantBuffer<ConstantBufferNum>							m_constantBuffer{};
		RenderTargetBuffer<RenderTargetBufferNum, BackBufferNum>	m_renderTargetBuffer{};
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray)
	{
		std::vector<ID3D12DescriptorHeap*> descriptorHeapArray{};
		descriptorHeapArray.reserve(heapParamArray.size());

		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:

				descriptorHeapArray.push_back(m_basicDescriptorHeap.getPtr(heapParam.m_id));
				break;

			case DescriptorHeapType::rtv:

				descriptorHeapArray.push_back(m_rtvDescriptorHeap.getPtr(heapParam.m_id));
				break;
			}
		}

		commandList->SetDescriptorHeaps(descriptorHeapArray.size(), descriptorHeapArray.data());

		for (const auto& heapParam : heapParamArray)
		{
			switch (heapParam.m_type)
			{
			case DescriptorHeapType::basic:

				m_basicDescriptorHeap.setDescriptor(heapParam.m_id, device, commandList);
				break;

			case DescriptorHeapType::rtv:

				m_rtvDescriptorHeap.setDescriptor(heapParam.m_id, device, commandList);
				break;
			}
		}
	}

	template<int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const
	{
		m_rtvDescriptorHeap.setRenderTarget(id, device, commandList, startRtvLocation, rtvCount);
	}

	template<int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color)
	{
		m_rtvDescriptorHeap.clearRenderTarget(id, device, commandList, rtvLocationIndex, color);
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam)
	{
		m_basicDescriptorHeap.create(id, device, initParam);

		auto cpuHeapHandleArray = m_basicDescriptorHeap.getCpuHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case BasicDescriptorType::constantBuffer:
	
				m_constantBuffer.createConstantBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
	
			case BasicDescriptorType::textureBuffer:
	
				m_textureBuffer.createShaderResourceView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam)
	{
		m_rtvDescriptorHeap.create(id, device, initParam);

		auto cpuHeapHandleArray = m_rtvDescriptorHeap.getCpuHeapHandleArray(id, device);

		for (unsigned int i = 0; i < initParam.m_descriptorParamArray.size(); i++)
		{
			switch (initParam.m_descriptorParamArray.at(i).m_type)
			{
			case RtvDescriptorType::normal:

				break;

			case RtvDescriptorType::backBuffer:

				m_renderTargetBuffer.createBackBufferView(initParam.m_descriptorParamArray.at(i).m_id, device, cpuHeapHandleArray.at(i));
				break;
			}
		}
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.cpuPriorityCreate(id, device, formatParam, dataParam);
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureBuffer.gpuPriorityCreate(id, device, commandList, formatParam, dataParam);
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.cpuPriorityLoad(id, device, formatParam, texDataPath);
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath)
	{
		m_textureBuffer.gpuPriorityLoad(id, device, commandList, formatParam, texDataPath);
	}

	template<int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		m_renderTargetBuffer.createBackBuffer(id, swapChain, backBufferIndex);
	}

	template<int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.useBackBuffer(id, commandList);
	}

	template<int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList)
	{
		m_renderTargetBuffer.unUseBackBuffer(id, commandList);
	}

	template <int BasicDescriptorHeapNum, int RtvDescriptorHeapNum, int TextureBufferNum, int ConstantBufferNum, int RenderTargetBufferNum, int BackBufferNum>
	template<class ConstantBufferDataType>
	inline void DescriptorHeap<BasicDescriptorHeapNum, RtvDescriptorHeapNum, TextureBufferNum, ConstantBufferNum, RenderTargetBufferNum, BackBufferNum>::createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		m_constantBuffer.create(id, device, rawConstantBufferData);
	}
}
#endif // !DESCRIPTOR_HEAP_H_