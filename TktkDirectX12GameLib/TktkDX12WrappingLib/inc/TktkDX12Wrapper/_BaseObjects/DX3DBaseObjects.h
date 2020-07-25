#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <vector>
#include <d3d12.h>
#include <dxgi1_6.h> //IDXGIFactory6
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../SwapChain/SwapChain.h"
#include "../Fence/Fence.h"
#include "../Resource/DX3DResource.h"

namespace tktk
{
	// DirectX12�̕`����s�����߂̃��C���}�l�[�W���[
	class DX3DBaseObjects
	{
	public:

		DX3DBaseObjects(const DX3DResourceInitParam& initParam, HWND hwnd, const tktkMath::Vector2& windowSize, const tktkMath::Color& backGroundColor);
		~DX3DBaseObjects();

	public: /* �`��J�n�A�I������ */

		// �`��J�n
		void beginDraw();

		// �`��I��
		void endDraw();

	public: /* ���\�[�X�쐬�A���[�h���� */

		// ���[�g�V�O�l�`�������
		void createRootSignature(unsigned int id, const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����
		void createPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		void createCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����
		void createRtBuffer(unsigned int id, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����
		void createDsBuffer(unsigned int id, const DepthStencilBufferInitParam& initParam);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����
		void createRtvDescriptorHeap(unsigned int id, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������
		void cpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`�������i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		void gpuPriorityCreateTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h����
		void cpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h����i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		void gpuPriorityLoadTextureBuffer(unsigned int id, const std::string& texDataPath);

	public: /* ���\�[�X�X�V���� */

		// �w�i�F��ݒ肷��
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �w��̒萔�o�b�t�@���X�V����
		void updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

	public: /* ���\�[�X���擾���� */

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

	public: /* ���\�[�X���R�}���h���X�g�ɓo�^���鏈�� */

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		void setOnlyDsv(unsigned int id) const;

		// �o�b�N�o�b�t�@�[��ݒ肷��
		void setBackBufferView() const;

		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(unsigned int dsvDescriptorHeapId) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int id) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int id) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int id) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// �v���~�e�B�u�g�|���W��ݒ肷��
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const;

	public: /* �h���[�R�[���A���̑����� */

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		) const;

		// �R�}���h���X�g�����s����
		void executeCommandList();

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

		ID3D12Device*				m_device				{ nullptr };
		IDXGIFactory6*				m_factory				{ nullptr };
		ID3D12CommandAllocator*		m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*	m_commandList			{ nullptr };
		ID3D12CommandQueue*			m_commandQueue			{ nullptr };
		SwapChain					m_swapChain				{};
		Fence						m_fence					{};
		DX3DResource				m_dX3DResource;
		tktkMath::Color				m_backGroundColor{ tktkMath::colorBlue };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_