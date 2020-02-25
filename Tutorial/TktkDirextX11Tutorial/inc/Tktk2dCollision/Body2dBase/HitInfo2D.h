#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <string>
#include <TktkMath/Vector2.h>

// 衝突判定の結果
struct HitInfo2D
{
public:

	HitInfo2D()
		: isHit(false)
		, selfPointClosestToOther(Vector2::zero)
		, otherPointClosestToSelf(Vector2::zero)
	{}

public:

	// 衝突したか？
	bool isHit;

	// 自身の当たり判定の中心座標から見て 相手の当たり判定に一番近い座標
	Vector2 selfPointClosestToOther;

	// 相手の当たり判定の中心座標から見て 自身の当たり判定に一番近い座標
	Vector2 otherPointClosestToSelf;
};

#endif // !HIT_INFO_2D_H_