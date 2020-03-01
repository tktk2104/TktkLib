#ifndef DEPTH_STENCIL_VIEW_H_
#define DEPTH_STENCIL_VIEW_H_

#include <type_traits>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/DepthStencilViewData.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// 「DepthStencilViewManager」の実装の一部を隠すためのクラス
	class DepthStencilView
	{
	public:

		// 新たな深度ビューを作成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でビューを作る場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize)
		{
			createImpl(static_cast<int>(id), useTextureSize);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// 指定した深度ビューを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※この関数でビューを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// 指定した深度ビューを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const DepthStencilViewData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const DepthStencilViewData& getData(IdType id) { static_assert(false, "DepthStencilViewId Fraud Type"); return nullptr; }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Vector2& useTextureSize);
		static void eraseImpl(int id);
		static const DepthStencilViewData& getDataImpl(int id);
	};
}
#endif // !DEPTH_STENCIL_VIEW_H_
