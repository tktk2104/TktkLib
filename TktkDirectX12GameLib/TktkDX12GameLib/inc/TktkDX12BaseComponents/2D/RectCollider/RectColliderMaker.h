#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include "RectCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class RectColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		RectColliderMaker() = default;
		RectColliderMaker(const RectColliderMaker& other) = default;
		RectColliderMaker& operator = (const RectColliderMaker& other) = default;


	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<RectCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		RectColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		RectColliderMaker& rectSize(const tktkMath::Vector2& value);

		// �����蔻��̃��[�J�����W��ݒ�
		RectColliderMaker& localPosition(const tktkMath::Vector2& value);

	private:

		// ���g�̃|�C���^
		static RectColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector2	m_rectSize			{ tktkMath::vec2One };
		tktkMath::Vector2	m_localPosition		{ tktkMath::vec2Zero };
	};
}
#endif // !RECT_COLLIDER_MAKER_H_