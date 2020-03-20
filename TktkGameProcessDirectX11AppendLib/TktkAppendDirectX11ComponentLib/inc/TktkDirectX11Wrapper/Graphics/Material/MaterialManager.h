#ifndef MATERIAL_MANAGER_H_
#define MATERIAL_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/MaterialAssets.h"
#include "Asset/SystemMaterialId.h"

namespace tktk
{
	// �uMaterialAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class MaterialManager
	{
	public:

		// �uMaterialAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ}�e���A���𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class MaterialIdType, class VSIdType, class PSIdType, class... TextureIds, std::enable_if_t<is_idType_all_v<MaterialIdType, VSIdType, PSIdType, TextureIds...>>* = nullptr>
		static void create(MaterialIdType id, VSIdType useVSId, PSIdType usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, TextureIds... useTextureIds)
		{
			createImpl(static_cast<int>(id), static_cast<int>(useVSId), static_cast<int>(usePSId), ambient, diffuse, specular, emission, shiniess, { static_cast<int>(useTextureIds)... });
		}
		template <class MaterialIdType, class VSIdType, class PSIdType, class... TextureIds, std::enable_if_t<!is_idType_all_v<MaterialIdType, VSIdType, PSIdType, TextureIds...>>* = nullptr>
		static void create(MaterialIdType id, VSIdType useVSId, PSIdType usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, TextureIds... useTextureIds)
		{ static_assert(false, "Id Fraud Type"); }

		// �}�e���A���𕡐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId)
		{
			duplicateImpl(static_cast<int>(id), static_cast<int>(originalId));
		}
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<!is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId) { static_assert(false, "Id Fraud Type"); }

		// �w�肵���}�e���A�����폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// �}�e���A�����Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// �S�Ẵ}�e���A�����폜����
		static void clear();

	
		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, int useVSId, int usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, const std::vector<int>& useTextureIdArray);
	private:
		static void duplicateImpl(int id, int originalId);
		static void eraseImpl(int id);
		static MaterialData* getDataPtrImpl(int id);

	private:

		static CfpPtr<MaterialAssets> m_assetsPtr;
	};
}
#endif // !MATERIAL_MANAGER_H_