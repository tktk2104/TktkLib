#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include "BoxCollider.h"

namespace tktk
{
	// BoxCollider�̃C���X�^���X���쐬����N���X
	class BoxColliderMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BoxColliderMaker() = default;
		BoxColliderMaker(const BoxColliderMaker& other) = default;
		BoxColliderMaker& operator = (const BoxColliderMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static BoxColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BoxCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		BoxColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		BoxColliderMaker& boxSize(const tktkMath::Vector3& value);

		// �����蔻��̃��[�J�����W��ݒ�
		BoxColliderMaker& localPosition(const tktkMath::Vector3& value);

	private:

		// ���g�̃|�C���^
		static BoxColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		int					m_collisionGroupType{ 0 };
		tktkMath::Vector3	m_boxSize			{ tktkMath::vec3One };
		tktkMath::Vector3	m_localPosition		{ tktkMath::vec3Zero };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_