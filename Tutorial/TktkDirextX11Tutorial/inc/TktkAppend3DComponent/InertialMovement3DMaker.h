#ifndef INERTIAL_MOVEMENT_3D_MAKER_H_
#define INERTIAL_MOVEMENT_3D_MAKER_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "InertialMovement3D.h"

namespace tktk
{
	// InertialMovement3D�̃C���X�^���X���쐬����N���X
	class InertialMovement3DMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static InertialMovement3DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<InertialMovement3D> craete();

		// ���x���P�b�Ԃłǂꂾ�����������邩��ݒ�
		InertialMovement3DMaker& decelerationPerSec(float value);

		// �������x��ݒ�
		InertialMovement3DMaker& initVelocity(const Vector3& value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static InertialMovement3DMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_decelerationPerSec{ 64.0f };
		Vector3 m_initVelocity{ Vector3::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_MAKER_H_