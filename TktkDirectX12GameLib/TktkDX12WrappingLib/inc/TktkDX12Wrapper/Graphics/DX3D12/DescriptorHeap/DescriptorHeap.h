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
	class DescriptorHeap
	{
	public:

		DescriptorHeap(int basicDescriptorHeapNum, int rtvDescriptorHeapNum, int textureBufferNum, int constantBufferNum, int renderTargetBufferNum, int backBufferNum);

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

		BasicDescriptorHeap	m_basicDescriptorHeap;
		RtvDescriptorHeap	m_rtvDescriptorHeap;
		
		TextureBuffer		m_textureBuffer;
		ConstantBuffer		m_constantBuffer;
		RenderTargetBuffer	m_renderTargetBuffer;
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