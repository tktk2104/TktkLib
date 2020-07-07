#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	// �uBasicDescriptorHeapData�v���Ǘ�����N���X
	class BasicDescriptorHeap
	{
	public:

		BasicDescriptorHeap(unsigned int basicDescriptorHeapNum);
		~BasicDescriptorHeap() = default;

	public:

		// �uBasicDescriptorHeapData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̃|�C���^���擾����
		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<BasicDescriptorHeapData> m_basicDescriptorHeapDataArray;
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_