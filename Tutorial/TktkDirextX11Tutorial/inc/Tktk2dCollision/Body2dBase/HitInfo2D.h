#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <string>
#include <TktkMath/Vector2.h>

// �Փ˔���̌���
struct HitInfo2D
{
public:

	HitInfo2D()
		: isHit(false)
		, selfPointClosestToOther(Vector2::zero)
		, otherPointClosestToSelf(Vector2::zero)
	{}

public:

	// �Փ˂������H
	bool isHit;

	// ���g�̓����蔻��̒��S���W���猩�� ����̓����蔻��Ɉ�ԋ߂����W
	Vector2 selfPointClosestToOther;

	// ����̓����蔻��̒��S���W���猩�� ���g�̓����蔻��Ɉ�ԋ߂����W
	Vector2 otherPointClosestToSelf;
};

#endif // !HIT_INFO_2D_H_