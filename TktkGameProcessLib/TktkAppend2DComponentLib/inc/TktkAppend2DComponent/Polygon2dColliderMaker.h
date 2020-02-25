#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Polygon2dCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class Polygon2dColliderMaker
	{
	public:

		// インスタンス作成開始
		static Polygon2dColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<Polygon2dCollider> create();

		// 当たり判定のグループを設定
		Polygon2dColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		Polygon2dColliderMaker& vertexs(const std::vector<Vector2>& value);

		// 当たり判定のローカル座標を設定
		Polygon2dColliderMaker& localPosition(const Vector2& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static Polygon2dColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		std::vector<Vector2> m_vertexs{};
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_