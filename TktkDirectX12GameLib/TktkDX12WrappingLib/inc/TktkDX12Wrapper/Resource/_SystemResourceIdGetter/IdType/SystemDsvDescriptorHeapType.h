#ifndef SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̐�
	constexpr unsigned int SystemDsvDescriptorHeapNum = 2U;

	// �V�X�e���Ŏg�p���Ă���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̎��
	enum class SystemDsvDescriptorHeapType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DSV_DESCRIPTOR_HEAP_TYPE_H_