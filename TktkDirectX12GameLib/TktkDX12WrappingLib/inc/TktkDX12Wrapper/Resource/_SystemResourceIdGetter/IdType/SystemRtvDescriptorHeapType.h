#ifndef SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̐�
	constexpr unsigned int SystemRtvDescriptorHeapNum = 1U;

	// �V�X�e���Ŏg�p���Ă��郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̎��
	enum class SystemRtvDescriptorHeapType
	{
		BackBuffer = 0U
	};
}
#endif // !SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_