#ifndef BUFFER_RESOURCE_H_
#define BUFFER_RESOURCE_H_

#include "BufferResourceInitParam.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "ConstantBuffer/ConstantBuffer.h"
#include "TextureBuffer/TextureBuffer.h"
#include "DepthStencilBuffer/DepthStencilBuffer.h"
#include "RenderTargetBuffer/RenderTargetBuffer.h"

namespace tktk
{
	class BufferResource
	{
	public:

		BufferResource(const BufferResourceInitParam& initParam);
		~BufferResource() = default;

	public: /* ���_�o�b�t�@�̏��� */

		void createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public: /* �C���f�b�N�X�o�b�t�@�̏��� */

		void createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public: /* �萔�o�b�t�@�̏��� */

		void createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		void createConstantBufferView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public: /* �e�N�X�`���o�b�t�@�̏��� */

		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		void createShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	public: /* �[�x�X�e���V���o�b�t�@�̏��� */

		void createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);

		void createDepthStencilView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

	public: /* �����_�[�^�[�Q�b�g�o�b�t�@�̏��� */

		void createRenderTargetBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		void createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		void createRenderTargetView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);
		void createRtvShaderResourceView(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		void useAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);
		void unUseAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		void useBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);
		void unUseBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		VertexBuffer		m_vertexBuffer;
		IndexBuffer			m_indexBuffer;
		ConstantBuffer		m_constantBuffer;
		TextureBuffer		m_textureBuffer;
		DepthStencilBuffer	m_depthStencilBuffer;
		RenderTargetBuffer	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_