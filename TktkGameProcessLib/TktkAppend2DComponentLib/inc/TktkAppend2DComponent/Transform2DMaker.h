#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkMath/Vector2.h>
#include "Transform2D.h"

namespace tktk
{
	// Transform2Dのインスタンスを作成するクラス
	class Transform2DMaker
	{
	public:

		// インスタンス作成開始
		static Transform2DMaker& makeStart();

	public:

		// 作成する
		Transform2D* create();

		// 座標を設定
		Transform2DMaker& position(const Vector2& value);

		// スケールを設定
		Transform2DMaker& scaleRate(const Vector2& value);

		// 回転角度を設定
		Transform2DMaker& rotationDeg(float value);

		// 親のTransform2Dとの関係性を設定
		Transform2DMaker& traceType(TraceParentType value);

	private:

		// 自身のポインタ
		static Transform2DMaker m_self;

	private:

		Vector2 m_initPosition{ Vector2::zero };
		Vector2 m_initScaleRate{ Vector2::one };
		float m_initRotationDeg{ 0.0f };
		TraceParentType m_traceType{ TraceParentType::TRACE_PARENT_ALL };
	};
}
#endif // !TRANSFORM_2D_MAKER_H_