#ifndef INERTIAL_MOVEMENT_2D_MAKER_H_
#define INERTIAL_MOVEMENT_2D_MAKER_H_

#include <TktkMath/Vector2.h>
#include "InertialMovement2D.h"

namespace tktk
{
	// InertialMovement2D�̃C���X�^���X���쐬����N���X
	class InertialMovement2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement2DMaker& makeStart();

	public:

		// �쐬����
		InertialMovement2D* create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement2DMaker& initVelocity(const Vector2& value);

	private:

		// ���g�̃|�C���^
		static InertialMovement2DMaker m_self;

	private:

		float m_decelerationPerSec{ 64.0f };
		Vector2 m_initVelocity{ Vector2::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_MAKER_H_