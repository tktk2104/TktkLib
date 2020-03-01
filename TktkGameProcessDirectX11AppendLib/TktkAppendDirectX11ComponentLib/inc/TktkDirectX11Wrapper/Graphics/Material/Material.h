#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/MaterialData.h"

namespace tktk
{
	// �uMaterialManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Material
	{
	public:

		// �V���ȃ}�e���A���𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ń}�e���A�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class MaterialIdType, class VertexShaderIdType, class PixelShaderIdType, std::enable_if_t<is_idType_all_v<MaterialIdType, VertexShaderIdType, PixelShaderIdType>>* = nullptr>
		static void create(
			MaterialIdType id,
			int indexBufferStartPos,
			int indexBufferUseCount,
			VertexShaderIdType useVertexShaderId,
			PixelShaderIdType usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shiniess
		)
		{
			createImpl(
				static_cast<int>(id),
				indexBufferStartPos,
				indexBufferUseCount,
				static_cast<int>(useVertexShaderId),
				static_cast<int>(usePixelShaderId),
				useTextureIdMap,
				ambientColor,
				diffuseColor,
				specularColor,
				emissionColor,
				shiniess
			);
		}
		template <class MaterialIdType, class VertexShaderIdType, class PixelShaderIdType, std::enable_if_t<!is_idType_all_v<MaterialIdType, VertexShaderIdType, PixelShaderIdType>>* = nullptr>
		static void create(
			MaterialIdType id,
			int indexBufferStartPos,
			int indexBufferUseCount,
			VertexShaderIdType useVertexShaderId,
			PixelShaderIdType usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shiniess
		) {
			static_assert(false, "Id Fraud Type");
		}

		// �}�e���A���𕡐�����
		// �����̊֐��Ń}�e���A�������ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ��i��������id�̒l�̐����͂Ȃ��j
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId)
		{
			duplicateImpl(static_cast<int>(id), static_cast<int>(originalId));
		}
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<!is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId) { static_assert(false, "Id Fraud Type"); }

		// �w�肵���}�e���A�����폜����
		// �����̊֐��Ń}�e���A�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// �}�e���A�����Ǘ�����N���X�̃|�C���^���擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(
			int id,
			int indexBufferStartPos,
			int indexBufferUseCount,
			int useVertexShaderId,
			int usePixelShaderId,
			const std::unordered_map<unsigned int, int>& useTextureIdMap,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Color& emissionColor,
			float shiniess
		);
		static void duplicateImpl(int id, int originalId);
		static void eraseImpl(int id);
		static MaterialData* getDataPtrImpl(int id);
	};
}
#endif // !MATERIAL_H_