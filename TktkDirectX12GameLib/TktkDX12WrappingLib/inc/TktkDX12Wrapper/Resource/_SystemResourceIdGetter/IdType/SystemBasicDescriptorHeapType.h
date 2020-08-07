#ifndef SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���ʏ�̃f�B�X�N���v�^�q�[�v�̐�
	constexpr unsigned int SystemBasicDescriptorHeapNum = 3U;

	// �V�X�e���Ŏg�p���Ă���ʏ�̃f�B�X�N���v�^�q�[�v�̎��
	enum class SystemBasicDescriptorHeapType
	{
		Line2D				= 0U,
		Sphere,
		BasicMeshShadowMap
	};
}
#endif // !SYSTEM_BASIC_DESCRIPTOR_HEAP_TYPE_H_