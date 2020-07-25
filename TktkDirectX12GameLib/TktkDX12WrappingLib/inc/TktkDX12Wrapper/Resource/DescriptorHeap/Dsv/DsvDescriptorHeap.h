#ifndef DSV_DESCRIPTOR_HEAP_H_
#define DSV_DESCRIPTOR_HEAP_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DsvDescriptorHeapData.h"

namespace tktk
{
	// �uDsvDescriptorHeapData�v���Ǘ�����N���X
	class DsvDescriptorHeap
	{
	public:

		DsvDescriptorHeap(unsigned int dsvDescriptorHeapNum);
		~DsvDescriptorHeap() = default;

	public:

		// �uDsvDescriptorHeapData�v�̃C���X�^���X�����
		void create(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă���[�x�X�e���V���o�b�t�@��ID�̔z����擾����
		const std::vector<unsigned int>& getDsBufferIdArray(unsigned int id) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̃|�C���^���擾����
		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �����_�[�^�[�Q�b�g�r���[��o�^�����Ɏw�肵���f�B�X�N���v�^�q�[�v�̐[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �[�x�X�e���V���r���[��S�ăN���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<DsvDescriptorHeapData> m_dsvDescriptorHeapDataArray;
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_H_