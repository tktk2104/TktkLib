#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3D�̃C���X�^���X���쐬����N���X
	class InertialMovement3DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		InertialMovement3DMaker() = default;
		InertialMovement3DMaker(const InertialMovement3DMaker& other) = default;
		InertialMovement3DMaker& operator = (const InertialMovement3DMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<InertialMovement3D> craete();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement3DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement3DMaker& initVelocity(const tktkMath::Vector3& value);

	private:

		// ���g�̃|�C���^
		static InertialMovement3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		float				m_decelerationPerSec{ 64.0f };
		tktkMath::Vector3	m_initVelocity		{ tktkMath::vec3Zero };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_