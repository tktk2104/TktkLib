#ifndef RECT_COLLIDER_H_
#define RECT_COLLIDER_H_

#include <forward_list>
#include <TktkMath/Vector2.h>
#include <Tktk2dCollision/Body2dBase/Body2dBase.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend2DComponent/Transform2D.h"

namespace tktk
{
	// �����`�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class RectCollider
		: public ComponentBase
	{
	public:

		RectCollider(
			int collisionGroupType,			// �����蔻��̃O���[�v�ԍ�
			const Vector2& rectSize,		// �����蔻��̑傫��
			const Vector2& localPosition	// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void update();
		bool isCollide(ProcessingClassPtr other);
		void onCollide(ProcessingClassPtr other);
		void afterCollide();

	public:

		// �����蔻��̃N���X���擾
		const Body2dBase& getBodyBase() const;

	private:

		// ���̃t���[���ŏՓ˂���GameObject�̃��X�g
		std::forward_list<CfpPtr<GameObject>> m_curHitObjectList;

		// �O�̃t���[���ŏՓ˂���GameObject�̃��X�g
		std::forward_list<CfpPtr<GameObject>> m_preHitObjectList;

		// �Փ˔��茋��
		HitInfo2D m_hitInfo;

		// �Q�����|���S���̏Փ˔���N���X
		BoundingPolygon2d m_boundingPolygon2d;

		// ���g�̂Q�������W�R���|�[�l���g
		CfpPtr<Transform2D> m_transform2D;
	};
}
#endif // !RECT_COLLIDER_H_