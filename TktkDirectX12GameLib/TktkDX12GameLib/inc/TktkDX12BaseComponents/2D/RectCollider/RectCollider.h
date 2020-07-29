#ifndef RECT_COLLIDER_H_
#define RECT_COLLIDER_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingPolygon2d.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// �����`�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class RectCollider
		: public ComponentBase
	{
	public:

		RectCollider(
			int collisionGroupType,					// �����蔻��̃O���[�v�ԍ�
			const tktkMath::Vector2& rectSize,		// �����蔻��̑傫��
			const tktkMath::Vector2& localPosition	// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// �����蔻��̃N���X���擾
		const Body2dBase& getBodyBase() const;

	private:

		// �Փ˔��茋��
		HitInfo2D m_hitInfo;

		// �Q�����|���S���̏Փ˔���N���X
		BoundingPolygon2d m_boundingPolygon2d;

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D> m_transform2D;
	};
}
#endif // !RECT_COLLIDER_H_