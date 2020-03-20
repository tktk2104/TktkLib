#ifndef SYSTEM_SPHERE_MESH_MAKER_H_
#define SYSTEM_SPHERE_MESH_MAKER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	class SystemSphereMeshMaker
	{
	public:

		// 0�ȉ���ID�ŋ��̃��b�V���p�̃��\�[�X������֐�
		template <class MeshIdType, class MaterialIdType, std::enable_if_t<is_idType_all_v<MeshIdType, MaterialIdType>>* = nullptr>
		static void make(MeshIdType meshId, MaterialIdType materialId)
		{
			makeImpl(static_cast<int>(meshId), static_cast<int>(materialId));
		}
		template <class MeshIdType, class MaterialIdType, std::enable_if_t<!is_idType_all_v<MeshIdType, MaterialIdType>>* = nullptr>
		static void make(MeshIdType meshId, MaterialIdType materialId) { static_assert(false, "MeshId Fraud Type"); }

	private:

		static void makeImpl(int meshId, int materialId);
	};
}
#endif // !SYSTEM_SPHERE_MESH_MAKER_H_
