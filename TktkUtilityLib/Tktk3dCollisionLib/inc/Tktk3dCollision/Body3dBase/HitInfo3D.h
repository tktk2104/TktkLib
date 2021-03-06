#ifndef HIT_INFO_3D_H_
#define HIT_INFO_3D_H_

#include <string>
#include <TktkMath/Vector3.h>

// 衝突判定の結果
struct HitInfo3D
{
public:

	HitInfo3D()
		: isHit(false)
		, selfPointClosestToOther(Vector3::zero)
		, otherPointClosestToSelf(Vector3::zero)
	{}

public:

	// 衝突したか？
	bool isHit;

	// 自身の当たり判定の中心座標から見て 相手の当たり判定に一番近い座標
	Vector3 selfPointClosestToOther;

	// 相手の当たり判定の中心座標から見て 自身の当たり判定に一番近い座標
	Vector3 otherPointClosestToSelf;
};

#endif // !HIT_INFO_3D_H_