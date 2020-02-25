#ifndef INERTIAL_MOVEMENT_2D_MAKER_H_
#define INERTIAL_MOVEMENT_2D_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "InertialMovement2D.h"

namespace tktk
{
	// InertialMovement2D�̃C���X�^���X���쐬����N���X
	class InertialMovement2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<InertialMovement2D> create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement2DMaker& initVelocity(const Vector2& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static InertialMovement2DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_decelerationPerSec{ 64.0f };
		Vector2 m_initVelocity{ Vector2::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_MAKER_H_