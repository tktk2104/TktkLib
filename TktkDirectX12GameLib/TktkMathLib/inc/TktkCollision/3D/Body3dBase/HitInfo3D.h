#ifndef HIT_INFO_3D_H_
#define HIT_INFO_3D_H_

#include <string>
#include "../../../TktkMath/Structs/Vector3.h"

// �Փ˔���̌���
struct HitInfo3D
{
public:

	HitInfo3D()
		: isHit(false)
		, selfPointClosestToOther(tktkMath::vec3Zero)
		, otherPointClosestToSelf(tktkMath::vec3Zero)
	{}

public:

	// �Փ˂������H
	bool isHit;

	// ���g�̓����蔻��̒��S���W���猩�� ����̓����蔻��Ɉ�ԋ߂����W
	tktkMath::Vector3 selfPointClosestToOther;

	// ����̓����蔻��̒��S���W���猩�� ���g�̓����蔻��Ɉ�ԋ߂����W
	tktkMath::Vector3 otherPointClosestToSelf;
};

#endif // !HIT_INFO_3D_H_