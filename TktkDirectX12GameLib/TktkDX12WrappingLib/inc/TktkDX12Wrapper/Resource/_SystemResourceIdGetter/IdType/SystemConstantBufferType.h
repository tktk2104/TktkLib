#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���萔�o�b�t�@�̐�
	constexpr unsigned int SystemCBufferNum = 6U;

	// �V�X�e���Ŏg�p���Ă���萔�o�b�t�@�̎��
	enum class SystemCBufferType
	{
		Sprite				= 0U,
		MeshTransform		= 1U,
		MeshShadowMap		= 2U,
		BoneMatCbuffer		= 3U,
		Light				= 4U,
		BasicMeshMaterial	= 5U
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_