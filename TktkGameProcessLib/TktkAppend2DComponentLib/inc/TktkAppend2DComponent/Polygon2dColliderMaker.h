#ifndef POLYGON_2D_COLLIDER_MAKER_H_
#define POLYGON_2D_COLLIDER_MAKER_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include "Polygon2dCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class Polygon2dColliderMaker
	{
	public:

		// インスタンス作成開始
		static Polygon2dColliderMaker& makeStart();

	public:

		// 作成する
		Polygon2dCollider* create();

		// 当たり判定のグループを設定
		Polygon2dColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		Polygon2dColliderMaker& vertexs(const std::vector<Vector2>& value);

		// 当たり判定のローカル座標を設定
		Polygon2dColliderMaker& localPosition(const Vector2& value);

	private:

		// 自身のポインタ
		static Polygon2dColliderMaker m_self;

	private:

		int m_collisionGroupType{ 0 };
		std::vector<Vector2> m_vertexs{};
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !POLYGON_2D_COLLIDER_MAKER_H_