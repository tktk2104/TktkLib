#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include "DescriptorHeapInitParam.h"
#include "DescriptorHeapParam.h"

#include "Basic/BasicDescriptorHeap.h"
#include "Rtv/RtvDescriptorHeap.h"
#include "Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	// �R��ނ̃f�B�X�N���v�^�q�[�v���Ǘ�����N���X
	class DescriptorHeap
	{
	public:

		DescriptorHeap(const DescriptorHeapInitParam& initParam);

	public: /* �R�}���h���X�g�ɓo�^���鏈�� */

		// �w��̃f�B�X�N���v�^�q�[�v�𕡐��܂Ƃ߂ăR�}���h���X�g�ɓo�^����
		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray);

	public: /* �����_�[�^�[�Q�b�g�A�[�x�X�e���V�����R�}���h���X�g�ɓo�^���鏈�� */

		// �����_�[�^�[�Q�b�g�r���[���R�}���h���X�g�ɓo�^����
		void setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;
		
		// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setRtvAndDsv(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount);
		
		// �����_�[�^�[�Q�b�g�r���[��o�^�����Ɏw�肵���f�B�X�N���v�^�q�[�v�̐[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		
	public: /* �f�B�X�N���v�^�q�[�v�����e�r���[�̃N���A���� */
		
		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�����w��̃����_�[�^�[�Q�b�g�r���[���N���A����
		void clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color);
		
		// �[�x�X�e���V���r���[��S�ăN���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	public: /* �쐬���� */

		// �ʏ�̃f�B�X�N���v�^�q�[�v�����
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		
		// �����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�����
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		
		// �[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�����
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* CPU�n���h���̎擾���� */

		// �w�肵���ʏ�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuBasicHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		
		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuRtvHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		
		// �w�肵���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuDsvHeapHandleArray(unsigned int id, ID3D12Device* device) const;

	public: /* �f�B�X�N���v�^�q�[�v�����e�r���[���Q�Ƃ��Ă���o�b�t�@��ID���擾���鏈�� */

		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă��郌���_�[�^�[�Q�b�g�o�b�t�@��ID�̔z����擾����
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;
		
		// �w�肵���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă���[�x�X�e���V���o�b�t�@��ID�̔z����擾����
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	private:

		BasicDescriptorHeap	m_basicDescriptorHeap;
		RtvDescriptorHeap	m_rtvDescriptorHeap;
		DsvDescriptorHeap	m_dsvDescriptorHeap;
	};
}
#endif // !DESCRIPTOR_HEAP_H_