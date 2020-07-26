#ifndef HIT_INFO_2D_H_
#define HIT_INFO_2D_H_

#include <string>
#include "../../../TktkMath/Structs/Vector2.h"

// �Փ˔���̌���
struct HitInfo2D
{
public:

	HitInfo2D()
		: isHit(false)
		, selfPointClosestToOther(tktkMath::vec2Zero)
		, otherPointClosestToSelf(tktkMath::vec2Zero)
	{}

public:

	// �Փ˂������H
	bool isHit;

	// ���g�̓����蔻��̒��S���W���猩�� ����̓����蔻��Ɉ�ԋ߂����W
	tktkMath::Vector2 selfPointClosestToOther;

	// ����̓����蔻��̒��S���W���猩�� ���g�̓����蔻��Ɉ�ԋ߂����W
	tktkMath::Vector2 otherPointClosestToSelf;
};

#endif // !HIT_INFO_2D_H_