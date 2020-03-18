#ifndef MESH_H_
#define MESH_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Assets/MeshData.h"

namespace tktk
{
	class Mesh
	{
	public:

		// �V���ȃ��b�V���f�[�^���쐬����
		// �����̊֐��Ń��b�V���f�[�^���쐬����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, D3D_PRIMITIVE_TOPOLOGY primitiveTopology, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams)
		{
			createImpl(static_cast<int>(id), primitiveTopology, vertexBufferParams, indexBufferParams, materialSlotsParams);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, D3D_PRIMITIVE_TOPOLOGY primitiveTopology, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams)
			{ static_assert(false, "MeshId Fraud Type"); }

		// �w�肵�����b�V���f�[�^���폜����
		// �����̊֐��Ń��b�V���f�[�^���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MeshId Fraud Type"); }

		// �w�肵�����b�V���f�[�^���Ǘ�����N���X�̃|�C���^���擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MeshData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MeshData* getDataPtr(IdType id) { static_assert(false, "MeshId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, D3D_PRIMITIVE_TOPOLOGY primitiveTopology, const VertexBufferInitParams& vertexBufferParams, const IndexBufferInitParams& indexBufferParams, const MaterialSlotsInitParams& materialSlotsParams);
		static void eraseImpl(int id);
		static MeshData* getDataPtrImpl(int id);
	};
}
#endif // !MESH_H_
