#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2D�̃C���X�^���X���쐬����N���X
	class InertialRotatement2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		InertialRotatement2DMaker() = default;
		InertialRotatement2DMaker(const InertialRotatement2DMaker& other) = default;
		InertialRotatement2DMaker& operator = (const InertialRotatement2DMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static InertialRotatement2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<InertialRotatement2D> create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialRotatement2DMaker& initVelocity(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		// ���g�̃|�C���^
		static InertialRotatement2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr	m_user					{ };
		float			m_decelerationPerSec	{ 30.0f };
		float			m_initVelocity			{ 0.0f };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_