#ifndef INERTIAL_MOVEMENT_2D_MAKER_H_
#define INERTIAL_MOVEMENT_2D_MAKER_H_

#include "InertialMovement2D.h"

namespace tktk
{
	// InertialMovement2D�̃C���X�^���X���쐬����N���X
	class InertialMovement2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		InertialMovement2DMaker() = default;
		InertialMovement2DMaker(const InertialMovement2DMaker& other) = default;
		InertialMovement2DMaker& operator = (const InertialMovement2DMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<InertialMovement2D> create();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement2DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement2DMaker& initVelocity(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		// ���g�̃|�C���^
		static InertialMovement2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr m_user			{ };
		float m_decelerationPerSec		{ 64.0f };
		tktkMath::Vector2 m_initVelocity{ tktkMath::vec2Zero };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_MAKER_H_