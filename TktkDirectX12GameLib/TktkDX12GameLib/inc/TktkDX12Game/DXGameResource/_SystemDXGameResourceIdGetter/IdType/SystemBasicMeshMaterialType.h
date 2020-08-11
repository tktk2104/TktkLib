#ifndef SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_
#define SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���ʏ�̃��b�V���}�e���A���̐�
	constexpr unsigned int SystemBasicMeshMaterialNum = 2U;

	// �V�X�e���Ŏg�p���Ă���ʏ�̃��b�V���}�e���A���̎��
	enum class SystemBasicMeshMaterialType
	{
		Sphere = 0U,
		SphereWireFrame
	};
}
#endif // !SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_