#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include "DX3DResourceInitParam.h"
#include "_SystemResourceIdGetter/SystemResourceIdGetter.h"
#include "Viewport/Viewport.h"
#include "ScissorRect/ScissorRect.h"
#include "GraphicsPipeLine/GraphicsPipeLine.h"
#include "DescriptorHeap/DescriptorHeap.h"
#include "Buffer/BufferResource.h"

namespace tktk
{
	// DirectX12�̃��\�[�X���Ǘ�����N���X
	class DX3DResource
	{
	public:

		// ���Ӑ}�I�ɒl���R�s�[���Ă��܂�
		DX3DResource(DX3DResourceInitParam initParam);

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
		void createCBuffer(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		void createRtBuffer(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�[�����烌���_�[�^�[�Q�b�g�o�b�t�@���擾����
		void createRtBuffer(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �[�x�X�e���V���o�b�t�@�����
		void createDsBuffer(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����
		void cpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		void gpuPriorityCreateTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���ăo�b�t�@�����
		void cpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���ăo�b�t�@�����i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		void gpuPriorityLoadTextureBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* ���\�[�X�X�V�n���� */

		// �w��̒��_�o�b�t�@���X�V����
		void updateVertexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �w��̃C���f�b�N�X�o�b�t�@���X�V����
		void updateIndexBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// �w��̒萔�o�b�t�@���X�V����
		void updateCBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* ���\�[�X���擾�n���� */

		// �w��̃o�b�t�@�̃e�N�X�`���Ƃ��ẴT�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�[��ID���擾����
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�[��ID���擾����
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	public: /* �`�揀�� */

		// �����_�[�^�[�Q�b�g�r���[���R�}���h���X�g�ɐݒ肷��
		void setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		// �������_�[�^�[�Q�b�g�r���[�͐ݒ�ł��Ȃ�
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�[�r���[��ݒ肷��
		void setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �o�b�N�o�b�t�@�[�r���[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(unsigned int rtvDescriptorHeapId, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(unsigned int dsvDescriptorHeapId, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* �f�t�H���g�̃��\�[�X���g�����߂�ID���擾���� */

		// �f�t�H���g�̃r���[�|�[�gID���擾����
		unsigned int getSystemId(SystemViewportType type) const;

		// �f�t�H���g�̃V�U�[��`ID���擾����
		unsigned int getSystemId(SystemScissorRectType type) const;

		// �f�t�H���g�̒��_�o�b�t�@ID���擾����
		unsigned int getSystemId(SystemVertexBufferType type) const;

		// �f�t�H���g�̃C���f�b�N�X�o�b�t�@ID���擾����
		unsigned int getSystemId(SystemIndexBufferType type) const;

		// �f�t�H���g�̒萔�o�b�t�@ID���擾����
		unsigned int getSystemId(SystemCBufferType type) const;

		// �f�t�H���g�̃e�N�X�`���o�b�t�@ID���擾����
		unsigned int getSystemId(SystemTextureBufferType type) const;

		// �f�t�H���g�̃����_�[�^�[�Q�b�g�o�b�t�@ID���擾����
		unsigned int getSystemId(SystemRtBufferType type) const;

		// �f�t�H���g�̐[�x�X�e���V���o�b�t�@ID���擾����
		unsigned int getSystemId(SystemDsBufferType type) const;

		// �f�t�H���g�̒ʏ�̃f�B�X�N���v�^�q�[�vID���擾����
		unsigned int getSystemId(SystemBasicDescriptorHeapType type) const;

		// �f�t�H���g�̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�vID���擾����
		unsigned int getSystemId(SystemRtvDescriptorHeapType type) const;

		// �f�t�H���g�̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�vID���擾����
		unsigned int getSystemId(SystemDsvDescriptorHeapType type) const;

		// �f�t�H���g�̃��[�g�V�O�l�`��ID���擾����
		unsigned int getSystemId(SystemRootSignatureType type) const;

		// �f�t�H���g�̃p�C�v���C���X�e�[�gID���擾����
		unsigned int getSystemId(SystemPipeLineStateType type) const;

	private:

		// �����̃o�b�t�@��񂪒萔�o�b�t�@�ł���Β萔�o�b�t�@�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

		// �����̃o�b�t�@��񂪃V�F�[�_�[���\�[�X�ɂȂ��o�b�t�@�ł���΃V�F�[�_�[���\�[�X�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

	private:

		SystemResourceIdGetter	m_sysResIdGetter;

		Viewport				m_viewport;
		ScissorRect				m_scissorRect;
		GraphicsPipeLine		m_graphicsPipeLine;
		DescriptorHeap			m_descriptorHeap;
		BufferResource			m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_