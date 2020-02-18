#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include <TktkMath/Vector2.h>
#include "CircleCollider.h"

namespace tktk
{
	// CircleCollider�̃C���X�^���X���쐬����N���X
	class CircleColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static CircleColliderMaker& makeStart();

	public:

		// �쐬����
		CircleCollider* create();

		// �����蔻��̃O���[�v��ݒ�
		CircleColliderMaker& collisionGroupType(int value);

		// �����蔻��̔��a��ݒ�
		CircleColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		CircleColliderMaker& localPosition(const Vector2& value);

	private:

		// ���g�̃|�C���^
		static CircleColliderMaker m_self;

	private:

		int m_collisionGroupType{ 0 };
		float m_radius{ 1.0f };
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_