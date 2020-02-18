#ifndef VIEW_PORT_H_
#define VIEW_PORT_H_

#include "Asset/ViewPortData.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	class ViewPort
	{
	public:

		// 新たなビューポートを生成する
		// ※この関数でビューポートを作る場合、idは1以上でなければならない
		static void create(int id, const Vector2& position, const Vector2& size);

		// 指定したビューポートを削除する
		// ※この関数でビューポートを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// 指定したビューポートを管理するクラスの参照を取得する
		static const ViewPortData& getData(int id);
	};
}
#endif // !VIEW_PORT_H_