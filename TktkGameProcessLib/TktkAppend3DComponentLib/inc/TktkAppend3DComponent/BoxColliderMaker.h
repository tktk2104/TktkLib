#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include "BoxCollider.h"

namespace tktk
{
	// BoxColliderのインスタンスを作成するクラス
	class BoxColliderMaker
	{
	public:

		// インスタンス作成開始
		static BoxColliderMaker& makeStart();

	public:

		// 作成する
		BoxCollider* create();

		// 当たり判定のグループを設定
		BoxColliderMaker& collisionGroupType(int value);

		// 当たり判定の大きさを設定
		BoxColliderMaker& boxSize(const Vector3& value);

		// 当たり判定のローカル座標を設定
		BoxColliderMaker& localPosition(const Vector3& value);

	private:

		// 自身のポインタ
		static BoxColliderMaker m_self;

	private:

		int m_collisionGroupType{ -1 };
		Vector3 m_boxSize{ Vector3::one };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_