#ifndef DRAW_PRIORITY_H_
#define DRAW_PRIORITY_H_

// 数字が小さい方が先に描画される
namespace DrawPriority
{
	// シャドウマップの生成を開始
	const float DRAW_PRIORITY_CREATE_SHADOW_BEGIN	= -500.0f;

	// シャドウマップの生成を行う描画優先度
	const float DRAW_PRIORITY_CREATE_SHADOW			= -400.0f;

	// シャドウマップの生成を終了
	const float DRAW_PRIORITY_CREATE_SHADOW_END		= -300.0f;

	// シャドウマップの適応を開始
	const float DRAW_PRIORITY_SHADOW_ENABLE			= -200.0f;

	// 空の描画
	const float DRAW_PRIORITY_SKY					= -100.0f;

	// 基本の描画優先度
	const float DRAW_PRIORITY_DEFAULT				= 0.0f;

	// シャドウマップの適応を終了
	const float DRAW_PRIORITY_SHADOW_DISABLE		= 100.0f;

	// 影を落とさないオブジェクト用の描画優先度
	const float DRAW_PRIORITY_NOT_DRAW_SHADOW		= 200.0f;
}
#endif // !DRAW_PRIORITY_H_