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

		// �O���t�B�b�N�p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(unsigned int id, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����
		void createVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����
		void createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����
		void createConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �[�x�X�e���V���o�b�t�@�����
		void createDepthStencilBuffer(unsigned int id, const tktkMath::Vector2& depthStencilSize);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, const BasicDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, const DsvDescriptorHeapInitParam& initParam);

		// gpu�D��Ńe�N�X�`�������[�h����
		void gpuPriorityLoadTextureBuffer(unsigned int id, const TexBufFormatParam& formatParam, const std::string& texDataPath);

	public:

		// �w��̒萔�o�b�t�@���X�V����
		void updateConstantBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̃e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector3& getTextureSize(unsigned int id) const;

	public:

		// �w�i�F��ݒ肷��
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g���R�}���h���X�g�ɐݒ肷��
		void setBackBufferRenderTarget();

		// �o�b�N�o�b�t�@�[�p�̃����_�[�^�[�Q�b�g�Ǝw��̃f�v�X�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		void setUseDepthStencilBackBufferRenderTarget(unsigned int dsvDescriptorHeapId);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id);

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id);

		// �w��̃O���t�B�b�N�p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setGraphicsPipeLineState(unsigned int id);

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
}
#endif // !DX3D_BASE_OBJECTS_H_