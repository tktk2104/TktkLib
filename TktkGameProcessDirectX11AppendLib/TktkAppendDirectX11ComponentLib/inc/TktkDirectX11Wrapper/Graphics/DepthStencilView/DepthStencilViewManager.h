#ifndef DEPTH_STENCIL_VIEW_MANAGER_H_
#define DEPTH_STENCIL_VIEW_MANAGER_H_

#include <type_traits>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilViewAssets.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// 「DepthStencilViewAssets」に簡単にアクセスするためのクラス
	class DepthStencilViewManager
	{
	public:

		// 「DepthStencilViewAssets」を生成
		static void setUp();

	public:

		// 新たな深度ビューを作成する 各種id指定系の関数の実装（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize)
		{
			createImpl(static_cast<int>(id), useTextureSize);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// 指定した深度ビューを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
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

		// 全ての深度ビューを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Vector2& useTextureSize);
		static void eraseImpl(int id);
		static const DepthStencilViewData& getDataImpl(int id);

	private:

		static CfpPtr<DepthStencilViewAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_VIEW_MANAGER_H_
