#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���萔�o�b�t�@�̐�
	constexpr unsigned int SystemCBufferNum = 8U;

	// �V�X�e���Ŏg�p���Ă���萔�o�b�t�@�̎��
	enum class SystemCBufferType
	{
		Sprite				= 0U,
		Line2D,
		MeshTransform,
		MeshShadowMap,
		BoneMatCbuffer,
		Light,
		BasicMeshMaterial,
		BasicMonoColorMeshCbuffer
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_