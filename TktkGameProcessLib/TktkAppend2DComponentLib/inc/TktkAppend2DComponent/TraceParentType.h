#ifndef TRACE_PARENT_TYPE_H_
#define TRACE_PARENT_TYPE_H_

namespace tktk
{
	// 親のTransformとの関係性の種類
	enum TraceParentType
	{
		// 親の座標のみを参照する
		TRACE_PARENT_POS = 1 << 0,

		// 親のスケールのみを参照する
		TRACE_PARENT_SCALE = 1 << 1,

		// 親の回転のみを参照する
		TRACE_PARENT_ROTATION = 1 << 2,

		// 親のTransformを参照しない
		NOT_TRACE_PARENT = 0,

		// 親の座標とスケールを参照する
		TRACE_PARENT_POS_AND_SCALE = TRACE_PARENT_POS | TRACE_PARENT_SCALE,

		// 親の座標と回転を参照する
		TRACE_PARENT_POS_AND_ROTATION = TRACE_PARENT_POS | TRACE_PARENT_ROTATION,

		// 親のスケールと回転を参照する
		TRACE_PARENT_SCALE_AND_ROTATION = TRACE_PARENT_SCALE | TRACE_PARENT_ROTATION,

		// 親のTransformを完全に参照する
		TRACE_PARENT_ALL = TRACE_PARENT_POS | TRACE_PARENT_SCALE | TRACE_PARENT_ROTATION,
	};
}

#endif // !TRACE_PARENT_TYPE_H_