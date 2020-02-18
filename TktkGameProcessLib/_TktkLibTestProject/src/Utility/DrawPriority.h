#pragma once

// 数字が小さい方が先に描画される
namespace DrawPriority
{
	// 前
	const float DRAW_PRIORITY_FAST = -10.0f;

	// 中
	const float DRAW_PRIORITY_MIDDLE = 0.0f;

	// 後
	const float DRAW_PRIORITY_LATE = 10.0f;
}