#ifndef COLLISION_SUPPORT_3D_H_
#define COLLISION_SUPPORT_3D_H_

#include "HitInfo3D.h"

class Body3dBase;

class CollisionSupport3D
{
public:
	
	// ���̂Ƌ��̂̓����蔻��
	static bool collideSphereToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D * hitinfo);

	// AABB��AABB�̓����蔻��
	static bool collideAabbToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D * hitinfo);

	// ���̂�AABB�̓����蔻��
	static bool collideSphereToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D * hitinfo);

	// AABB�Ƌ��̂̓����蔻��iCollideSphereToAabb()�̏������s������AHitInfo��self��other�����ւ���j
	static bool collideAabbToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D * hitinfo);
};

#endif // !COLLISION_SUPPORT_3D_H_