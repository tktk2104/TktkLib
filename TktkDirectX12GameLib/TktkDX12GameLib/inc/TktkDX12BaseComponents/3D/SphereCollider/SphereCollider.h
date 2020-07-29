#ifndef SPHERE_COLLIDER_H_
#define SPHERE_COLLIDER_H_

#include <TktkMath/Structs/Vector3.h>
#include <TktkCollision/3D/BoundingSphere.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

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
			const tktkMath::Vector3& localPosition	// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// �����蔻��̃N���X���擾
		const Body3dBase& getBodyBase() const;

		// ���O�̏Փ˔���̌��ʂ��擾
		const HitInfo3D& getHitInfo3D() const;

	private:

		// �Փ˔��茋��
		HitInfo3D m_hitInfo;

		// ���̂̏Փ˔���N���X
		BoundingSphere m_boundingSphere;

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !SPHERE_COLLIDER_H_