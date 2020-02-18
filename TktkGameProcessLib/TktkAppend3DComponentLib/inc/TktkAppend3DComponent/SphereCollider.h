#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Vector3.h>
#include <Tktk3dCollision/Body3dBase/Body3dBase.h>
#include <Tktk3dCollision/BoundingSphere.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend3DComponent/Transform3D.h"

namespace tktk
{
	// ���̂̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class SphereCollider
		: public ComponentBase
	{
	public:

		SphereCollider(
			int collisionGroupType,			// �����蔻��̃O���[�v�ԍ�
			float radius,					// �����蔻��̔��a
			const Vector3& localPosition	// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void update();
		bool isCollide(ProcessingClassPtr other);
		void onCollide(ProcessingClassPtr other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const Body3dBase& getBodyBase() const;

		// ���O�̏Փ˔���̌��ʂ��擾
		const HitInfo3D& getHitInfo3D() const;

	private:

		// ���̃t���[���ŏՓ˂���GameObject�̃��X�g
		std::forward_list<CfpPtr<GameObject>> m_curHitObjectList;

		// �O�̃t���[���ŏՓ˂���GameObject�̃��X�g
		std::forward_list<CfpPtr<GameObject>> m_preHitObjectList;

		// �Փ˔��茋��
		HitInfo3D m_hitInfo;

		// ���̂̏Փ˔���N���X
		BoundingSphere m_boundingSphere;

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<Transform3D> m_transform3D;
	};
}
#endif // !SPHERE_COLLIDER_H_