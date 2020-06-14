#ifndef BASIC_DESCRIPTOR_HEAP_DATA_H_
#define BASIC_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include <d3d12.h>
#include "BasicDescriptorHeapInitParam.h"

namespace tktk
{
	class BasicDescriptorHeapData
	{
	public:

		BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		~BasicDescriptorHeapData();

	public:

		// �X�̃f�B�X�N���v�^�̃A�h���X�̃n���h�����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		ID3D12DescriptorHeap* getPtr() const;

		// �R�}���h���X�g�Ɏ��g��ݒ肷��
		void setDescriptor(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public:

		// ���ꂼ��̃f�B�X�N���v�^�e�[�u���������Ă���f�B�X�N���v�^�̐��̔z��
		std::vector<unsigned int> m_descriptorTableSizeArray;

		ID3D12DescriptorHeap*	m_descriptorHeap{ nullptr };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_DATA_H_