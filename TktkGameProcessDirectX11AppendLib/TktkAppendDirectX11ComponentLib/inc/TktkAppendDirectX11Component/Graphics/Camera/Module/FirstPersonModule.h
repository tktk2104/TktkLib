#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class FirstPersonModule
		: public ComponentBase
	{
	public:

		FirstPersonModule(
			float rotateDegSpeedPerSec,		// ���b�̉�]�p�x�i�x���@�j
			float moveSpeedPerSec,			// ���b�̈ړ����x
			bool alwaysMoveForward,			// ��ɑO���Ɉړ����邩
			bool enableUpDownKey			// �X�y�[�X�A�V�t�g�L�[�ŏ㉺�Ɉړ����邩
		);
		~FirstPersonModule();

	public:

		void start();
		void update();

	public:

		float* getRotateDegSpeedPerSecPtr();

		float* getMoveSpeedPerSecPtr();

		bool* getAlwaysMoveForwardPtr();

		bool* getEnableUpDownKeyPtr();

	private:

		void rotate();

		void moveHorizontal();

		void moveVertical();

	private:

		// ���g�̂R�������W�R���|�[�l���g
		CfpPtr<Transform3D> m_transform;

		// ���b�̉�]�p�x�i�x���@�j
		float m_rotateDegSpeedPerSec;

		// ���b�̈ړ����x
		float m_moveSpeedPerSec;

		// ��ɑO���Ɉړ����邩
		bool m_alwaysMoveForward{ false };

		// �X�y�[�X�A�V�t�g�L�[�ŏ㉺�Ɉړ����邩
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_H_