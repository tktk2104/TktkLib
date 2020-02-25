#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Quaternion.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "Transform3D.h"

namespace tktk
{
	// Transform3Dを作成するクラス
	class Transform3DMaker
	{
	public:

		// 作成開始
		static Transform3DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<Transform3D> create();

		// 初期座標を設定
		Transform3DMaker& position(const Vector3& value);

		// 初期スケールを設定
		Transform3DMaker& scaleRate(const Vector3& value);

		// 初期回転を設定（クオータニオンでの指定）
		Transform3DMaker& rotation(const Quaternion& value);

		// 初期回転を設定（オイラー角での指定）
		Transform3DMaker& rotationDeg(const Vector3& value);

		// 親のTransform3Dとの関係性を設定
		Transform3DMaker& traceType(TraceParentType value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static Transform3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		Vector3 m_initPosition{ Vector3::zero };
		Vector3 m_initScaleRate{ Vector3::one };
		Quaternion m_initRotation{ Quaternion::identity };
		TraceParentType m_traceType{ TraceParentType::TRACE_PARENT_ALL };
	};
}
#endif // !TRANSFORM_3D_MAKER_H_