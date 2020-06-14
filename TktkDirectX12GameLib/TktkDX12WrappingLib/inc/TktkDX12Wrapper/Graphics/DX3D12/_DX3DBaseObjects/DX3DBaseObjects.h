#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <vector>
#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "DX3DBaseObjectsInitParam.h"
#include "../Fence/Fence.h"
#include "../DX3DResource/DX3DResource.h"

namespace tktk
{
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor);
		~DX3DBaseObjects();

	public:

		// �`��J�n
		void beginDraw();

		// �`��I��
		void endDraw();

	public:

		// ���[�g�V�O�l�`�������
		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����
		void createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		void createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		void createRenderTargetBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����
		void createDepthStencilBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// cpu�D��Ńe�N�X�`�������
		void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// gpu�D��Ńe�N�X�`�������
		void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// cpu�D��Ńe�N�X�`�������[�h����
		void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// gpu�D��Ńe�N�X�`�������[�h����
		void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

	public:

		// �w��̒萔�o�b�t�@���X�V����
		void updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRenderTarget(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color);

		// �w��̃e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;
		const tktkMath::Vector2& getDepthStencilSize(unsigned int id) const;
		const tktkMath::Vector2& getRenderTargetSize(unsigned int id) const;

	public:

		// �w�i�F��ݒ肷��
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		void setRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		void setRenderTargetAndDepthStencil(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		void setOnlyDepthStencil(unsigned int id);

		// �o�b�N�o�b�t�@�[��ݒ肷��
		void setBackBuffer();

		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferAndDepthStencil(unsigned int dsvDescriptorHeapId);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRenderTarget(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount);

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDepthStencil(unsigned int dsvDescriptorHeapId);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id);

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id);

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int id);

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int id);

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int id);

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray);

		// �v���~�e�B�u�g�|���W��ݒ肷��
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);

	public:

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		);

		// �R�}���h���X�g�����s����
		void executeCommandList();

	public:

		template <class SystemResourceType>
		unsigned int getSystemId(SystemResourceType type) const;

	private:

		ID3D12Device*				m_device				{ nullptr };
		IDXGIFactory6*				m_factory				{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList			{ nullptr };
		ID3D12CommandQueue*			m_commandQueue			{ nullptr };
		IDXGISwapChain1*			m_swapChain				{ nullptr };
		unsigned int				m_curBackBufferIndex	{ 0U };
		Fence						m_fence					{};

		DX3DResource				m_dX3DResource;

		tktkMath::Color				m_backGroundColor{ tktkMath::colorBlue };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class SystemResourceType>
	inline unsigned int DX3DBaseObjects::getSystemId(SystemResourceType type) const
	{
		return m_dX3DResource.getSystemId(type);
	}
}
#endif // !DX3D_BASE_OBJECTS_H_