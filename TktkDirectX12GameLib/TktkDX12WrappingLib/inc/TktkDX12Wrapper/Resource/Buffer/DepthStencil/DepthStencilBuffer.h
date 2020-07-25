#ifndef DEPTH_STENCIL_BUFFER_H_
#define DEPTH_STENCIL_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DepthStencilBufferData.h"

namespace tktk
{
	// �uDepthStencilBufferData�v���Ǘ�����N���X
	class DepthStencilBuffer
	{
	public:

		DepthStencilBuffer(unsigned int depthStencilBufferNum);
		~DepthStencilBuffer() = default;

	public:

		// �uDepthStencilBufferData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allBeginWrite(ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allEndWrite(ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�A�G���[��f���܂�
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int id) const;

	private:

		HeapArray<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
