#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/MaterialData.h"
#include "Asset/SystemMaterialId.h"

namespace tktk
{
	// 「MaterialManager」の実装の一部を隠すためのクラス
	class Material
	{
	public:

		// 新たなマテリアルを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でマテリアルを作る場合、idは1以上でなければならない
		template <class MaterialIdType, class VSIdType, class PSIdType, class... TextureIds, std::enable_if_t<is_idType_all_v<MaterialIdType, VSIdType, PSIdType, TextureIds...>>* = nullptr>
		static void create(MaterialIdType id, VSIdType useVSId, PSIdType usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, TextureIds... useTextureIds)
		{
			createImpl(static_cast<int>(id), static_cast<int>(useVSId), static_cast<int>(usePSId), ambient, diffuse, specular, emission, shiniess, { static_cast<int>(useTextureIds)... });
		}
		template <class MaterialIdType, class VSIdType, class PSIdType, class... TextureIds, std::enable_if_t<!is_idType_all_v<MaterialIdType, VSIdType, PSIdType, TextureIds...>>* = nullptr>
		static void create(MaterialIdType id, VSIdType useVSId, PSIdType usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, TextureIds... useTextureIds)
		{ static_assert(false, "Id Fraud Type"); }

		// マテリアルを複製する
		// ※この関数でマテリアルを作る場合、idは1以上でなければならない（複製元のidの値の制限はない）
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId)
		{
			duplicateImpl(static_cast<int>(id), static_cast<int>(originalId));
		}
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<!is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId) { static_assert(false, "Id Fraud Type"); }

		// 指定したマテリアルを削除する
		// ※この関数でマテリアルを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// マテリアルを管理するクラスのポインタを取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, int useVSId, int usePSId, const Color& ambient, const Color& diffuse, const Color& specular, const Color& emission, float shiniess, const std::vector<int>& useTextureIdArray);
		static void duplicateImpl(int id, int originalId);
		static void eraseImpl(int id);
		static MaterialData* getDataPtrImpl(int id);
	};
}
#endif // !MATERIAL_H_