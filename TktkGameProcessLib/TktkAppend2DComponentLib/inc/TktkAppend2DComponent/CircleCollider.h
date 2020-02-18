#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Vector2.h>
#include <Tktk2dCollision/Body2dBase/Body2dBase.h>
#include <Tktk2dCollision/BoundingCircle.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend2DComponent/Transform2D.h"

namespace tktk
{
	// 真円の当たり判定のコンポーネント
	// 【前提コンポーネント：Transform2D】
	class CircleCollider
		: public ComponentBase
	{
	public:

		CircleCollider(
			int collisionGroupType,			// 当たり判定のグループ番号
			float radius,					// 当たり判定の半径
			const Vector2& localPosition	// 当たり判定のローカル座標
		);

	public:

		// <PolymorphismFunc>
		void update();
		bool isCollide(ProcessingClassPtr other);
		void onCollide(ProcessingClassPtr other);
		void afterCollide();

	public:

		// 当たり判定のクラスを取得
		const Body2dBase& getBodyBase() const;

		// 直前の衝突判定の結果を取得
		const HitInfo2D& getHitInfo2D() const;

	private:

		// 今のフレームで衝突したGameObjectのリスト
		std::forward_list<CfpPtr<GameObject>> m_curHitObjectList;

		// 前のフレームで衝突したGameObjectのリスト
		std::forward_list<CfpPtr<GameObject>> m_preHitObjectList;

		// 衝突判定結果
		HitInfo2D m_hitInfo;

		// 円の衝突判定クラス
		BoundingCircle m_boundingCircle;

		// 自身の２次元座標コンポーネント
		CfpPtr<Transform2D> m_transform2D;
	};
}
#endif // !CIRCLE_COLLIDER_H_