#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "BoxCollider.h"

namespace tktk
{
	// BoxColliderのインスタンスを作成するクラス
	class BoxColliderMaker
	{
	public:

		// インスタンス作成開始
		static BoxColliderMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<BoxCollider> create();

		// 当たり判定のグループを設定
		BoxColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		BoxColliderMaker& boxSize(const Vector3& value);

		// 当たり判定のローカル座標を設定
		BoxColliderMaker& localPosition(const Vector3& value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static BoxColliderMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		Vector3 m_boxSize{ Vector3::one };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_