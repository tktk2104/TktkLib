#ifndef SPHERE_COLLIDER_MAKER_H_
#define SPHERE_COLLIDER_MAKER_H_

#include <TktkMath/Vector3.h>
#include "SphereCollider.h"

namespace tktk
{
	// SphereCollider�̃C���X�^���X���쐬����N���X
	class SphereColliderMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SphereColliderMaker& makeStart();

	public:

		// �쐬����
		SphereCollider* create();

		// �����蔻��̃O���[�v��ݒ�
		SphereColliderMaker& collisionGroupType(int value);

		// �����蔻��̔��a��ݒ�
		SphereColliderMaker& radius(float value);

		// �����蔻��̃��[�J�����W��ݒ�
		SphereColliderMaker& localPosition(const Vector3& value);

	private:

		// ���g�̃|�C���^
		static SphereColliderMaker m_self;

	private:

		int m_collisionGroupType{ -1 };
		float m_radius{ 1.0f };
		Vector3 m_localPosition{ Vector3::zero };
	};
}
#endif // !SPHERE_COLLIDER_MAKER_H_