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
	// �U��ނ̃o�b�t�@���\�[�X���Ǘ�����N���X
	class BufferResource
	{
	public:

		BufferResource(const BufferResourceInitParam& initParam);
		~BufferResource() = default;

	public: /* �o�b�t�@���ʂ̏��� */

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	public: /* ���_�o�b�t�@�̏��� */

		// ���_�o�b�t�@�����
		void createVertexBuffer(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public: /* �C���f�b�N�X�o�b�t�@�̏��� */

		// �C���f�b�N�X�o�b�t�@�����
		void createIndexBuffer(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

	public: /* �萔�o�b�t�@�̏��� */

		// �萔�o�b�t�@�����
		void createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̒萔�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̒萔�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public: /* �e�N�X�`���o�b�t�@�̏��� */

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����
		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);
		
		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(unsigned int id) const;

	public: /* �[�x�X�e���V���o�b�t�@�̏��� */

		// �[�x�X�e���V���o�b�t�@�����
		void createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createDsSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWriteDsBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList);

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList);

		// �w��̐[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int id) const;

	public: /* �����_�[�^�[�Q�b�g�o�b�t�@�̏��� */

		// �[�����烌���_�[�^�[�Q�b�g�o�b�t�@�����
		void createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// �X���b�v�`�F�C�����烌���_�[�^�[�Q�b�g�o�b�t�@�����
		void createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createRtSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾���i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int id) const;

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