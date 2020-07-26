#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

#include "HitInfo2D.h"

class Body2dBase;
struct tktkMath::Vector2;

class CollisionSupport2D
{
public:

	// �~�Ɖ~�̓����蔻��
	static bool collideCircleToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �����`�ƒ����`�̓����蔻��
	static bool collideRectToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �|���S���ƃ|���S���̓����蔻��
	static bool collidePolygonToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �~�ƒ����`�̓����蔻��
	static bool collideCircleToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �����`�Ɖ~�̓����蔻��icollideCircleToRect()�̏������s������AHitInfo��self��other�����ւ���j
	static bool collideRectToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �~�ƃ|���S���̓����蔻��
	static bool collideCircleToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �|���S���Ɖ~�̓����蔻��icollideCircleToPolygon()�̏������s������AHitInfo��self��other�����ւ���j
	static bool collidePolygonToCircle(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �����`�ƃ|���S���̓����蔻��
	static bool collideRectToPolygon(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �|���S���ƒ����`�̓����蔻��icollideRectToPolygon()�̏������s������AHitInfo��self��other�����ւ���j
	static bool collidePolygonToRect(const Body2dBase& self, const Body2dBase& other, HitInfo2D * hitinfo);

	// �|���S���Ɠ_�̓����蔻��
	static bool collidePolygonToPoint(const Body2dBase& self, const tktkMath::Vector2& other);
};

#endif // !COLLISION_SUPPORT_2D_H_