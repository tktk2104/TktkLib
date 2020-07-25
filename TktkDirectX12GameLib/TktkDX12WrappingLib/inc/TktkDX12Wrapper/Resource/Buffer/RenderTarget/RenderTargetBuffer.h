#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	// �uRenderTargetBufferData�v���Ǘ�����N���X
	class RenderTargetBuffer
	{
	public:

		RenderTargetBuffer(unsigned int renderTargetBufferNum);
		~RenderTargetBuffer() = default;

	public:

		// �[������uRenderTargetBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�C������uRenderTargetBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾���i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int id) const;

	private:

		HeapArray<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_