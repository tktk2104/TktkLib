#ifndef BASIC_DESCRIPTOR_HEAP_DATA_H_
#define BASIC_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#include "BasicDescriptorHeapInitParam.h"

namespace tktk
{
	// �V�F�[�_�[���\�[�X�r���[�A�萔�o�b�t�@�r���[�ȂǗp�̃f�B�X�N���v�^�q�[�v�N���X
	class BasicDescriptorHeapData
	{
	public:

		BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		~BasicDescriptorHeapData();

	public:

		// �e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// �f�B�X�N���v�^�q�[�v���܂Ƃ߂ăR�}���h���X�g�ɓo�^���邽�߂ɂ���Q�b�^�[
		ID3D12DescriptorHeap* getPtr() const;

		// �e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public:

		// ���ꂼ��̃f�B�X�N���v�^�e�[�u���������Ă���f�B�X�N���v�^�̐��̔z��
		std::vector<unsigned int> m_descriptorTableSizeArray;

		ID3D12DescriptorHeap*	m_descriptorHeap{ nullptr };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_DATA_H_