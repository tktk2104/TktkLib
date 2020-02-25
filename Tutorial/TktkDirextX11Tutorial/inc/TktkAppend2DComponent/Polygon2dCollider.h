#ifndef POLYGON_2D_COLLIDER_H_
#define POLYGON_2D_COLLIDER_H_

#include <vector>
#include <forward_list>
#include <TktkMath/Vector2.h>
#include <Tktk2dCollision/Body2dBase/Body2dBase.h>
#include <Tktk2dCollision/BoundingPolygon2d.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend2DComponent/Transform2D.h"

namespace tktk
{
	// ���p�`�̓����蔻��̃R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class Polygon2dCollider
		: public ComponentBase
	{
	public:

		Polygon2dCollider(
			int collisionGroupType,					// �����蔻��̃O���[�v�ԍ�
			const std::vector<Vector2>& vertexs,	// �����蔻����\�����钸�_�̍��W�i���v���j
			const Vector2& localPosition			// �����蔻��̃��[�J�����W
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

		// ���O�̏Փ˔���̌��ʂ��擾
		const HitInfo2D& getHitInfo2D() const;

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
#endif // !POLYGON_2D_COLLIDER_H_