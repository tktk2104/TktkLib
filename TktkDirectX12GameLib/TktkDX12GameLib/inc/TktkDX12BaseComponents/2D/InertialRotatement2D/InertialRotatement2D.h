#ifndef INERTIAL_ROTATEMENT_2D_H_
#define INERTIAL_ROTATEMENT_2D_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// �Q�����̊�����]�R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class InertialRotatement2D
		: public ComponentBase
	{
	public:

		InertialRotatement2D(
			float decelerationPerSec,	// ���x���P�b�Ԃłǂꂾ�����������邩�H
			float initVelocity			// ������]���x
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// �u�ԓI�ɗ͂�������i�����̒l�����̂܂ܑ��x�ɉ�����j
		void addMomentarilyForce(float force);

		// �p���I�ɗ͂�������i�������̑��x��ڎw���āA���b�������̋����̑��x��������j
		// �����t���[���Ă�ł�������
		// �����������[���������ꍇ�͉������܂���
		void addContinuousForce(float force, float accelerationPerSec);

		// ���݂̉�]���x���擾
		float getVelocity() const;

		// ���݂̉�]���x��ݒ�
		void setVelocity(float velocity);

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D> m_transform2D;

		// ���x
		float m_velocity;

		// ���x���P�b�Ԃłǂꂾ�����������邩�H
		float m_decelerationPerSec;

		// �O�t���[���ŉ����������H
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_H_