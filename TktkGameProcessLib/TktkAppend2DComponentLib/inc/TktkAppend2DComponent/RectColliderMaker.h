#ifndef RECT_COLLIDER_MAKER_H_
#define RECT_COLLIDER_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectCollider.h"

namespace tktk
{
	// RectCollider�̃C���X�^���X���쐬����N���X
	class RectColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<RectCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		RectColliderMaker& collisionGroupType(int value);

		// �����蔻��̑傫����ݒ�
		RectColliderMaker& rectSize(const Vector2& value);

		// �����蔻��̃��[�J�����W��ݒ�
		RectColliderMaker& localPosition(const Vector2& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static RectColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		Vector2 m_rectSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
	};
}
#endif // !RECT_COLLIDER_MAKER_H_