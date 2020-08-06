#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

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
		~FirstPersonModule() = default;

	public:

		void start();
		void update();

	public:

		float getRotateDegSpeedPerSec();
		// ���b��]�p�x��ݒ肷��
		void setRotateDegSpeedPerSec(float deg);

		float getMoveSpeedPerSec();
		// ���b�ړ�������ݒ肷��
		void setMoveSpeedPerSec(float speed);

		bool getAlwaysMoveForward();
		// ��ɃJ�����̕����Ɉړ����邩��ݒ肷��i�ړ��L�[��y���̍��W��ω������邩�H�j
		void setAlwaysMoveForward(bool flag);

		bool getEnableUpDownKey();
		// �X�y�[�X�ƃV�t�g��y���̍��W��ω������邩��ݒ肷��
		void setEnableUpDownKey(bool flag);

	private:

		void rotate();

		void moveHorizontal();

		void moveVertical();

	private:

		// ���g�̂R�������W�R���|�[�l���g
		ComponentPtr<Transform3D> m_transform;

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