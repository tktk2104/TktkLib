#ifndef BOX_COLLIDER_MAKER_H_
#define BOX_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "BoxCollider.h"

namespace tktk
{
	// BoxCollider�̃C���X�^���X���쐬����N���X
	class BoxColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static BoxColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<BoxCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		BoxColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		BoxColliderMaker& boxSize(const Vector3& value);

		// �����蔻��̃��[�J�����W��ݒ�
		BoxColliderMaker& localPosition(const Vector3& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static BoxColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		Vector3 m_boxSize{ Vector3::one };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !BOX_COLLIDER_MAKER_H_