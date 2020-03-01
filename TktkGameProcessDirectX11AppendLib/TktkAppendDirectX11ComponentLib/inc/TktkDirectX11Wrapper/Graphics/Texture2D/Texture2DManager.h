#ifndef TEXTURE_2D_MANAGER_H_
#define TEXTURE_2D_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/Texture2DAssets.h"

namespace tktk
{
	// 「Texture2DAssets」に簡単にアクセスするためのクラス
	class Texture2DManager
	{
	public:

		// 「Texture2DAssets」を生成
		static void setUp();

	public:

		// 新たな2Dテクスチャをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "Texture2DId Fraud Type"); }

		// 指定した2Dテクスチャを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "Texture2DId Fraud Type"); }

		// 指定した2Dテクスチャを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const Texture2DData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const Texture2DData& getData(IdType id) { static_assert(false, "Texture2DId Fraud Type"); }

		// 全ての2Dテクスチャを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, const std::string& fileName);
		static void eraseImpl(int id);
		static const Texture2DData& getDataImpl(int id);

	private:

		static CfpPtr<Texture2DAssets> m_assetsPtr;
	};
}
#endif // !TEXTURE_2D_MANAGER_H_