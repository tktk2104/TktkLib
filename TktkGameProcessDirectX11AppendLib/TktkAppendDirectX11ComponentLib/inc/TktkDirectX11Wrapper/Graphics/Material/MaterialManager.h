#ifndef MATERIAL_MANAGER_H_
#define MATERIAL_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/MaterialAssets.h"

namespace tktk
{
	// 「MaterialAssets」に簡単にアクセスするためのクラス
	class MaterialManager
	{
	public:

		// 「MaterialAssets」を生成
		static void setUp();

	public:

		// 新たなマテリアルを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
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
		) { static_assert(false, "Id Fraud Type"); }

		// マテリアルを複製する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId)
		{
			duplicateImpl(static_cast<int>(id), static_cast<int>(originalId));
		}
		template <class CreateIdType, class OriginalIdType, std::enable_if_t<!is_idType_all_v<CreateIdType, OriginalIdType>>* = nullptr>
		static void duplicate(CreateIdType id, OriginalIdType originalId) { static_assert(false, "Id Fraud Type"); }

		// 指定したマテリアルを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// マテリアルを管理するクラスのポインタを取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static MaterialData* getDataPtr(IdType id) { static_assert(false, "MaterialId Fraud Type"); }

		// 全てのマテリアルを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
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

	private:

		static CfpPtr<MaterialAssets> m_assetsPtr;
	};
}
#endif // !MATERIAL_MANAGER_H_