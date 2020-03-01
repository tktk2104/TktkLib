#ifndef VIEW_PORT_H_
#define VIEW_PORT_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/ViewPortData.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	class ViewPort
	{
	public:

		// 新たなビューポートを生成する
		// ※この関数でビューポートを作る場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size)
		{
			createImpl(static_cast<int>(id), position, size);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size) { static_assert(false, "ViewPortId Fraud Type"); }

		// 指定したビューポートを削除する
		// ※この関数でビューポートを削除する場合、idは1以上でなければならない
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// 指定したビューポートを管理するクラスの参照を取得する
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

	private:

		// 各種id指定系の関数の実装
		static void createImpl(int id, const Vector2& position, const Vector2& size);
		static void eraseImpl(int id);
		static const ViewPortData& getDataImpl(int id);
	};
}
#endif // !VIEW_PORT_H_