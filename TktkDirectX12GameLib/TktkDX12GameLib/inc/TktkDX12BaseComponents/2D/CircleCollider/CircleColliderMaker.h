#ifndef CIRCLE_COLLIDER_MAKER_H_
#define CIRCLE_COLLIDER_MAKER_H_

#include "CircleCollider.h"

namespace tktk
{
	// CircleCollider�̃C���X�^���X���쐬����N���X
	class CircleColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		CircleColliderMaker() = default;
		CircleColliderMaker(const CircleColliderMaker& other) = default;
		CircleColliderMaker& operator = (const CircleColliderMaker& other) = default;

	public:

		// �쐬�J�n
		static CircleColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<CircleCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		CircleColliderMaker& collisionGroupType(int value);

		// �����蔻��̔��a��ݒ�
		CircleColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		CircleColliderMaker& localPosition(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		// ���g�̃|�C���^
		static CircleColliderMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user					{ };
		int					m_collisionGroupType	{ 0 };
		float				m_radius				{ 1.0f };
		tktkMath::Vector2	m_localPosition			{ tktkMath::vec2Zero };
	};
}
#endif // !CIRCLE_COLLIDER_MAKER_H_