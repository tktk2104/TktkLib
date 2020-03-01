#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/Texture2DData.h"

namespace tktk
{
	// 「Texture2DManager」の実装の一部を隠すためのクラス
	class Texture2D
	{
	public:

		// 新たな2Dテクスチャをロードする（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数で2Dテクスチャをロードする場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "Texture2DId Fraud Type"); }

		// 指定した2Dテクスチャを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数で2Dテクスチャを削除する場合、idは1以上でなければならない
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

	private:

		// 各種id指定系の関数の実装
		static void loadImpl(int id, const std::string& fileName);
		static void eraseImpl(int id);
		static const Texture2DData& getDataImpl(int id);
	};
}
#endif // !TEXTURE_2D_H_