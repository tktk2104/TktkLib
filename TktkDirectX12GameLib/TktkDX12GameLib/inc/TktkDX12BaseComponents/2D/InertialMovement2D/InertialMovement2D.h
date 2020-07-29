#ifndef INERTIAL_MOVEMENT_2D_H_
#define INERTIAL_MOVEMENT_2D_H_

#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

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
			const tktkMath::Vector2& initVelocity	// �������x
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// �u�ԓI�ɗ͂�������i�����̃x�N�g�������̂܂ܑ��x�ɉ�����j
		void addMomentarilyForce(const tktkMath::Vector2& force);

		// �p���I�ɗ͂�������i�������̃x�N�g����ڎw���āA���b�������̒����̃x�N�g���𑬓x�ɉ�����j
		// �����t���[���Ă�ł�������
		// �����������[���x�N�g���������ꍇ�͉������܂���
		void addContinuousForce(const tktkMath::Vector2& force, float accelerationPerSec);

		// ���݂̑��x���擾
		const tktkMath::Vector2& getVelocity() const;

		// ���݂̑��x��ݒ�
		void setVelocity(const tktkMath::Vector2& velocity);

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		ComponentPtr<Transform2D> m_transform2D;

		// ���x
		tktkMath::Vector2 m_velocity;

		// ���x���P�b�Ԃłǂꂾ�����������邩�H
		float m_decelerationPerSec;

		// �O�t���[���ŉ����������H
		bool m_preFrameAddForce{ false };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_H_