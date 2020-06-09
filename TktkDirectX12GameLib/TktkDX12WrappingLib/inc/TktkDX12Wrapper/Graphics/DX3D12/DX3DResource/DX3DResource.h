#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include "DX3DResourceInitParam.h"
#include "Viewport/Viewport.h"
#include "ScissorRect/ScissorRect.h"
#include "GraphicsPipeLine/GraphicsPipeLine.h"
#include "DescriptorHeap/DescriptorHeap.h"
#include "BufferResource/BufferResource.h"

namespace tktk
{
	class DX3DResource
	{
	public:

		DX3DResource(const DX3DResourceInitParam& initParam);

	public: /* �쐬�A���[�h���� */

		// �r���[�|�[�g�����
		void createViewport(unsigned int id, const std::vector<ViewportInitParam>& initParamArray);

		// �V�U�[��`�����
		void createScissorRect(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		// ���[�g�V�O�l�`�������
		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����
		void createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����
		void createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		void createConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		void createRenderTargetBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�[�����烌���_�[�^�[�Q�b�g�o�b�t�@���擾����
		void createRenderTargetBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �[�x�X�e���V���o�b�t�@�����
		void createDepthStencilBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& depthStencilSize);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// cpu�D��Ńe�N�X�`�������
		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// gpu�D��Ńe�N�X�`�������
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// cpu�D��Ńe�N�X�`�������[�h����
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);

		// gpu�D��Ńe�N�X�`�������[�h����
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

	public: /* ���\�[�X�X�V�n���� */

		// �w��̒萔�o�b�t�@���X�V����
		void updateConstantBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRenderTarget(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		void clearDepthStencilViewAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	public: /* ���\�[�X���擾�n���� */

		// �w��̃e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�[��ID���擾����
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	public: /* �`�揀�� */

		// �w��̃����_�[�^�[�Q�b�g���R�}���h���X�g�ɐݒ肷��
		void setRenderTarget(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̃����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

		// �����_�[�^�[�Q�b�g�o�b�t�@���������_�[�^�[�Q�b�g��Ԃɂ���
		void useAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �����_�[�^�[�Q�b�g�o�b�t�@���v���Z�b�g��Ԃɂ���
		void unUseAsRenderTargetBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �����_�[�^�[�Q�b�g�o�b�t�@���������_�[�^�[�Q�b�g��Ԃɂ���
		void useAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �����_�[�^�[�Q�b�g�o�b�t�@���v���Z�b�g��Ԃɂ���
		void unUseAsBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	private:

		Viewport			m_viewport;
		ScissorRect			m_scissorRect;
		GraphicsPipeLine	m_graphicsPipeLine;
		DescriptorHeap		m_descriptorHeap;
		BufferResource		m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_