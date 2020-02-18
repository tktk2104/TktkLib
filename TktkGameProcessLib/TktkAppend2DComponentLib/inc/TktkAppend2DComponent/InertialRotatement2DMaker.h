#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2D�̃C���X�^���X���쐬����N���X
	class InertialRotatement2DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static InertialRotatement2DMaker& makeStart();

	public:

		// �쐬����
		InertialRotatement2D* create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialRotatement2DMaker& initVelocity(float value);

	private:

		// ���g�̃|�C���^
		static InertialRotatement2DMaker m_self;

	private:

		float m_decelerationPerSec{ 30.0f };
		float m_initVelocity{ 0.0f };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_