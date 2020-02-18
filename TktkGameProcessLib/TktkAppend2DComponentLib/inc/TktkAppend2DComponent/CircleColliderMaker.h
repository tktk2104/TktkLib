#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include <TktkMath/Vector2.h>
#include "CircleCollider.h"

namespace tktk
{
	// CircleColliderのインスタンスを作成するクラス
	class CircleColliderMaker
	{
	public:

		// インスタンス作成開始
		static CircleColliderMaker& makeStart();

	public:

		// 作成する
		CircleCollider* create();

		// 当たり判定のグループを設定
		CircleColliderMaker& collisionGroupType(int value);

		// 当たり判定の半径を設定
		CircleColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		CircleColliderMaker& localPosition(const Vector2& value);

	private:

		// 自身のポインタ
		static CircleColliderMaker m_self;

	private:

		int m_collisionGroupType{ 0 };
		float m_radius{ 1.0f };
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_