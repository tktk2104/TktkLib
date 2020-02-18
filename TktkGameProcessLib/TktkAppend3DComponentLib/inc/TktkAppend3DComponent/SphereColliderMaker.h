#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereColliderのインスタンスを作成するクラス
	class SphereColliderMaker
	{
	public:

		// インスタンス作成開始
		static SphereColliderMaker& makeStart();

	public:

		// 作成する
		SphereCollider* create();

		// 当たり判定のグループを設定
		SphereColliderMaker& collisionGroupType(int value);

		// 当たり判定の半径を設定
		SphereColliderMaker& radius(float value);

		// 当たり判定のローカル座標を設定
		SphereColliderMaker& localPosition(const Vector3& value);

	private:

		// 自身のポインタ
		static SphereColliderMaker m_self;

	private:

		int m_collisionGroupType{ -1 };
		float m_radius{ 1.0f };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_