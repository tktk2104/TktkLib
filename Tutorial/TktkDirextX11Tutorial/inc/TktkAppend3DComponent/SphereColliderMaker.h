#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereCollider�̃C���X�^���X���쐬����N���X
	class SphereColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SphereColliderMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<SphereCollider> create();

		// �����蔻��̃O���[�v��ݒ�
		SphereColliderMaker& collisionGroupType(int value);

		// �����蔻��̔��a��ݒ�
		SphereColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		SphereColliderMaker& localPosition(const Vector3& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static SphereColliderMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		int m_collisionGroupType{ 0 };
		float m_radius{ 1.0f };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_