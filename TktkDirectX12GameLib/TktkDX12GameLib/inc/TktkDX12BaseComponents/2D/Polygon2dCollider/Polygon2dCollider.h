#ifndef POLYGON_2D_COLLIDER_H_
#define POLYGON_2D_COLLIDER_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkCollision/2D/BoundingPolygon2d.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// ���p�`�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class Polygon2dCollider
		: public ComponentBase
	{
	public:

		Polygon2dCollider(
			int collisionGroupType,							// �����蔻��̃O���[�v�ԍ�
			const std::vector<tktkMath::Vector2>& vertexs,	// �����蔻����\�����钸�_�̍��W�i���v���j
			const tktkMath::Vector2& localPosition			// �����蔻��̃��[�J�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();
		bool isCollide(const ComponentBasePtr& other);

	public:

		// �����蔻��̃N���X���擾
		const Body2dBase& getBodyBase() const;

		// ���O�̏Փ˔���̌��ʂ��擾
		const HitInfo2D& getHitInfo2D() const;

	private:

		// �Փ˔��茋��
		HitInfo2D m_hitInfo;

		// �Q�����|���S���̏Փ˔���N���X
		BoundingPolygon2d m_boundingPolygon2d;

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D> m_transform2D;
	};
}
#endif // !POLYGON_2D_COLLIDER_H_