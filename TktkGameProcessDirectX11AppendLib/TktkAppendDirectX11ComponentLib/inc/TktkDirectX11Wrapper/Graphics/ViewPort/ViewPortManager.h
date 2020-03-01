#ifndef VIEW_PORT_MANAGER_H_
#define VIEW_PORT_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ViewPortAssets.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	// 「ViewPortAssets」に簡単にアクセスするためのクラス
	class ViewPortManager
	{
	public:

		// 「ViewPortAssets」を生成
		static void setUp();

	public:

		// 新たなビューポートを生成する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size)
		{
			createImpl(static_cast<int>(id), position, size);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size) { static_assert(false, "ViewPortId Fraud Type"); }

		// 指定したビューポートを削除する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// 指定したビューポートを管理するクラスの参照を取得する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// 全てのビューポートを削除する
		static void clear();

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Vector2& position, const Vector2& size);
		static void eraseImpl(int id);
		static const ViewPortData& getDataImpl(int id);

	private:

		static CfpPtr<ViewPortAssets> m_assetsPtr;
	};
}
#endif // !VIEW_PORT_MANAGER_H_