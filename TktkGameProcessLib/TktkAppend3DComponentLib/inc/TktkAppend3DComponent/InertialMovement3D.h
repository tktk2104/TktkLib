#ifndef INERTIAL_MOVEMENT_3D_H_
#define INERTIAL_MOVEMENT_3D_H_

#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend3DComponent/Transform3D.h"

namespace tktk
{
	class InertialMovement3D
		: public ComponentBase
	{
	public:

		InertialMovement3D(
			float decelerationPerSec,		// ���x���P�b�Ԃłǂꂾ�����������邩�H
			const Vector3 & initVelocity	// �������x
		);

	public:

		// <PolymorphismFunc>
		void update();

	public:

		// �u�ԓI�ɗ͂�������i�����̃x�N�g�������̂܂ܑ��x�ɉ�����j
		void addMomentarilyForce(const Vector3& force);

		// �p���I�ɗ͂�������i�������̃x�N�g����ڎw���āA���b�������̒����̃x�N�g���𑬓x�ɉ�����j
		// �����t���[���Ă�ł�������
		// �����������[���x�N�g���������ꍇ�͉������܂���
		void addContinuousForce(const Vector3& force, float accelerationPerSec);

		// ���݂̑��x���擾
		Vector3 getVelocity() const;

		// ���݂̑��x��ݒ�
		void setVelocity(const Vector3& velocity);

	private:

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<Transform3D> m_transform3D;

		// ���x
		Vector3 m_velocity;

		// ���x���P�b�Ԃłǂꂾ�����������邩�H
		float m_decelerationPerSec;

		// �O�t���[���ŉ����������H
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_MOVEMENT_3D_H_