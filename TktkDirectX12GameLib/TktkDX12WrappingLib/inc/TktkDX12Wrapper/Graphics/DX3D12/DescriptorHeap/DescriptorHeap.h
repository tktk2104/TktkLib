#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include "DescriptorHeapParam.h"

#include "BasicDescriptorHeap/BasicDescriptorHeap.h"
#include "RtvDescriptorHeap/RtvDescriptorHeap.h"
#include "DsvDescriptorHeap/DsvDescriptorHeap.h"

#include "BufferResource/TextureBuffer/TextureBuffer.h"
#include "BufferResource/ConstantBuffer/ConstantBuffer.h"
#include "BufferResource/RenderTargetBuffer/RenderTargetBuffer.h"
#include "BufferResource/DepthStencilBuffer/DepthStencilBuffer.h"

namespace tktk
{
	class DescriptorHeap
	{
	public:

		DescriptorHeap(int basicDescriptorHeapNum, int rtvDescriptorHeapNum, int dsvDescriptorHeapNum, int textureBufferNum, int constantBufferNum, int renderTargetBufferNum, int backBufferNum, int depthStencilBufferNum);

	public:

		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

		void setRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const;
		void setRenderTargetAndDepthStencil(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount);
		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		void clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public:

		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
	
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const std::string& texDataPath);
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const std::string& texDataPath);
	
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	public:
	
		void createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		template <class ConstantBufferDataType>
		void createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData);

		void updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public:

		void createBackBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);
		void unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public:

		void createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);

	private:

		BasicDescriptorHeap	m_basicDescriptorHeap;
		RtvDescriptorHeap	m_rtvDescriptorHeap;
		DsvDescriptorHeap	m_dsvDescriptorHeap;
		
		TextureBuffer		m_textureBuffer;
		ConstantBuffer		m_constantBuffer;
		RenderTargetBuffer	m_renderTargetBuffer;
		DepthStencilBuffer	m_depthStencilBuffer;
	};
//„¬„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª
//„«‚±‚±‚©‚ç‰º‚ÍŠÖ”‚ÌÀ‘•
//„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª

	template<class ConstantBufferDataType>
	inline void DescriptorHeap::createConstantBuffer(unsigned int id, ID3D12Device* device, const ConstantBufferDataType& rawConstantBufferData)
	{
		m_constantBuffer.create(id, device, rawConstantBufferData);
	}
}
#endif // !DESCRIPTOR_HEAP_H_