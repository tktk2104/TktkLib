#ifndef INERTIAL_MOVEMENT_2D_H_
#define INERTIAL_MOVEMENT_2D_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppend2DComponent/Transform2D.h"

namespace tktk
{
	// �Q�����̊����ړ��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class InertialMovement2D
		: public ComponentBase
	{
	public:

		InertialMovement2D(
			float decelerationPerSec,				// ���x���P�b�Ԃłǂꂾ�����������邩�H
			const Vector2 & initVelocity			// �������x
		);

	public:

		// <PolymorphismFunc>
		void update();

	public:

		// �u�ԓI�ɗ͂�������i�����̃x�N�g�������̂܂ܑ��x�ɉ�����j
		void addMomentarilyForce(const Vector2& force);

		// �p���I�ɗ͂�������i�������̃x�N�g����ڎw���āA���b�������̒����̃x�N�g���𑬓x�ɉ�����j
		// �����t���[���Ă�ł�������
		// �����������[���x�N�g���������ꍇ�͉������܂���
		void addContinuousForce(const Vector2& force, float accelerationPerSec);

		// ���݂̑��x���擾
		const Vector2& getVelocity() const;

		// ���݂̑��x��ݒ�
		void setVelocity(const Vector2& velocity);

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		CfpPtr<Transform2D> m_transform2D;

		// ���x
		Vector2 m_velocity;

		// ���x���P�b�Ԃłǂꂾ�����������邩�H
		float m_decelerationPerSec;

		// �O�t���[���ŉ����������H
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_H_