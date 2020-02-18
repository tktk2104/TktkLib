#ifndef BOX_COLLIDER_H_
#define BOX_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Vector3.h>
#include <Tktk3dCollision/Body3dBase/Body3dBase.h>
#include <Tktk3dCollision/AxisAlignedBoundingBox.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend3DComponent/Transform3D.h"

namespace tktk
{
	// AABBの当たり判定のコンポーネント
	// 【前提コンポーネント：Transform3D】
	class BoxCollider
		: public ComponentBase
	{
	public:

		BoxCollider(
			int collisionGroupType,			// 当たり判定のグループ番号
			const Vector3& boxSize,			// 当たり判定の大きさ
			const Vector3& localPosition	// 当たり判定のローカル座標
		);

	public:

		// <PolymorphismFunc>
		void update();
		bool isCollide(ProcessingClassPtr other);
		void onCollide(ProcessingClassPtr other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const Body3dBase& getBodyBase() const;

		// 直前の衝突判定の結果を取得
		const HitInfo3D& getHitInfo3D() const;

	private:

		// 今のフレームで衝突したGameObjectのリスト
		std::forward_list<CfpPtr<GameObject>> m_curHitObjectList;

		// 前のフレームで衝突したGameObjectのリスト
		std::forward_list<CfpPtr<GameObject>> m_preHitObjectList;

		// 衝突判定結果
		HitInfo3D m_hitInfo;

		// AABBの衝突判定クラス
		AxisAlignedBoundingBox m_boundingBox;

		// 自身の３次元座標コンポーネント
		CfpPtr<Transform3D> m_transform3D;
	};
}
#endif // !BOX_COLLIDER_H_