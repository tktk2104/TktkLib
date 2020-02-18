#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3D�̃C���X�^���X���쐬����N���X
	class InertialMovement3DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement3DMaker& makeStart();

	public:

		// �쐬����
		InertialMovement3D* craete();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement3DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement3DMaker& initVelocity(const Vector3& value);

	private:

		// ���g�̃|�C���^
		static InertialMovement3DMaker m_self;

	private:

		float m_decelerationPerSec{ 64.0f };
		Vector3 m_initVelocity{ Vector3::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_