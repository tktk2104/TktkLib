#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	// �P�l�̓I��Transform3D���ړ�������R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class FirstPersonModule
		: public tktk::ComponentBase
	{
	public:

		FirstPersonModule(
			float rotationDegPerPixelOnMouseMove,	// �}�E�X�J�[�\�����P�s�N�Z���ړ��������̉�]�p�x�i�x���@�j
			float moveSpeedPerSec,					// ���b�ǂꂾ���̑��x�ňړ����邩
			bool alwaysMoveForward,					// ��ɑO���Ɉړ����邩
			bool enableUpDownKey					// �X�y�[�X�A�V�t�g�L�[�ŏ㉺�Ɉړ����邩
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	private:

		// �}�E�X����ɂ���]
		void rotateWithMouse();

		// ���������ւ̈ړ�
		void moveVertical();

		// wasd�L�[�ɂ��ړ�
		void inputToMove();

	private:

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<tktk::Transform3D> m_selfTransform;

		// �O�t���[���̃}�E�X�̍��W
		Vector2 m_preMousePos;

		// �}�E�X�J�[�\�����P�s�N�Z���ړ��������̉�]�p�x�i�x���@�j
		float m_rotationDegPerPixelOnMouseMove;

		// ���b�̈ړ����x
		float m_moveSpeedPerSec;

		// ��ɑO���Ɉړ����邩
		bool m_alwaysMoveForward{ false };

		// �X�y�[�X�A�V�t�g�L�[�ŏ㉺�Ɉړ����邩
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_H_