#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include "Body3dBase/Body3dBase.h"

class AxisAlignedBoundingBox;

// ����
// ���ȉ~�̂ł͂Ȃ�
class BoundingSphere
	: public Body3dBase
{
public:

	BoundingSphere(
		float radius,
		const Vector3 & localPosition = Vector3::zero
	);

	// �Փ˔���
	bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const override;

public:

	// ���s��̃X�P�[���̒l�͂��v�f�������g�p�����
	float calculateRadius() const;

	// ���s��̃X�P�[���̒l�͂��v�f�������g�p�����
	float calculateLocalRadius() const;

private:

	float m_radius;
};
#endif // !BOUNDING_SPHERE_H_