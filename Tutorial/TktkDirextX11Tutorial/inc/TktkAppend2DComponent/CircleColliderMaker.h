#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "CircleCollider.h"

namespace tktk
{
	// CircleColliderのインスタンスを作成するクラス
	class CircleColliderMaker
	{
	public:

		// 作成開始
		static CircleColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<CircleCollider> create();

		// 当たり判定のグループを設定
		CircleColliderMaker& collisionGroupType(int value);

		// 当たり判定の半径を設定
		CircleColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		CircleColliderMaker& localPosition(const Vector2& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static CircleColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		float m_radius{ 1.0f };
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_