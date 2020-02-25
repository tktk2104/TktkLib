#ifndef AXIS_ALIGNED_BOUNDING_BOX_H_
#define AXIS_ALIGNED_BOUNDING_BOX_H_

#include "Body3dBase/Body3dBase.h"

class BoundingSphere;

// AABB
// ����]�͊Ǌ��O�i��]����Ȃ�OBB���g�����j
class AxisAlignedBoundingBox 
	: public Body3dBase
{
public:

	AxisAlignedBoundingBox(
		const Vector3& boxSize,
		const Vector3& localPosition = Vector3::zero
	);

	// �Փ˔���
	bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const override;

public:

	// ���_�̎��
	enum class CornerType
	{
		LeftTopFront,
		RightTopFront,
		LeftBottomFront,
		RightBottomFront,

		LeftTopBack,
		RightTopBack,
		LeftBottomBack,
		RightBottomBack,

		Min = LeftBottomFront,
		Max = RightTopBack
	};

	// ���_���W���v�Z
	Vector3 calculateCornerPoint(CornerType cornerIndex) const;

	// �����蔻��̑傫�����v�Z
	Vector3 calculateBoxSize() const;

	// ���[�J���̓����蔻��̑傫�����v�Z
	Vector3 calculateLocalBoxSize() const;

private:

	Vector3 m_boxSize;
};
#endif // !AXIS_ALIGNED_BOUNDING_BOX_H_