#ifndef BOX_COLLIDER_H_
#define BOX_COLLIDER_H_

#include <TktkCollision/3D/AxisAlignedBoundingBox.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// AABB�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class BoxCollider
		: public ComponentBase
	{
	public:

		BoxCollider(
			int collisionGroupType,					// �����蔻��̃O���[�v�ԍ�
			const tktkMath::Vector3& boxSize,		// �����蔻��̑傫��
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

		// AABB�̏Փ˔���N���X
		AxisAlignedBoundingBox m_boundingBox;

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D> m_transform3D;
	};
}
#endif // !BOX_COLLIDER_H_