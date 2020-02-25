#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class RectColliderMaker
	{
	public:

		// インスタンス作成開始
		static RectColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<RectCollider> create();

		// 当たり判定のグループを設定
		RectColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		RectColliderMaker& rectSize(const Vector2& value);

		// 当たり判定のローカル座標を設定
		RectColliderMaker& localPosition(const Vector2& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static RectColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		Vector2 m_rectSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !RECT_COLLIDER_MAKER_H_