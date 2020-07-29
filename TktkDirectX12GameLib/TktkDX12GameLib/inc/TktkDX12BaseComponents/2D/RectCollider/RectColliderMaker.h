#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include "RectCollider.h"

namespace tktk
{
	// RectColliderのインスタンスを作成するクラス
	class RectColliderMaker
	{
	private: /* プライベートコンストラクタ達 */

		RectColliderMaker() = default;
		RectColliderMaker(const RectColliderMaker& other) = default;
		RectColliderMaker& operator = (const RectColliderMaker& other) = default;


	public:

		// インスタンス作成開始
		static RectColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<RectCollider> create();

		// 当たり判定のグループを設定
		RectColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		RectColliderMaker& rectSize(const tktkMath::Vector2& value);

		// 当たり判定のローカル座標を設定
		RectColliderMaker& localPosition(const tktkMath::Vector2& value);

	private:

		// 自身のポインタ
		static RectColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user				{ };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector2	m_rectSize			{ tktkMath::vec2One };
		tktkMath::Vector2	m_localPosition		{ tktkMath::vec2Zero };
	};
}
#endif // !RECT_COLLIDER_MAKER_H_