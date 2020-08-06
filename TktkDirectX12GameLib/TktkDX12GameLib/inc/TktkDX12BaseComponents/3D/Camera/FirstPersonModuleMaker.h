#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include "FirstPersonModule.h"

namespace tktk
{
	// �uFirstPersonModule�v�����w���p�[�N���X
	class FirstPersonModuleMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		FirstPersonModuleMaker() = default;
		FirstPersonModuleMaker(const FirstPersonModuleMaker& other) = default;
		FirstPersonModuleMaker& operator = (const FirstPersonModuleMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<FirstPersonModule> create();

	public:  /* �p�����[�^�ݒ�֐� */

		
		// �������b��]�p�x��ݒ肷��
		FirstPersonModuleMaker& rotateDegSpeedPerSec(float value);

		// �������b�ړ�������ݒ肷��
		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		// ��ɃJ�����̕����Ɉړ����邩��ݒ肷��i�ړ��L�[��y���̍��W��ω������邩�H�j
		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		// �X�y�[�X�ƃV�t�g��y���̍��W��ω������邩��ݒ肷��
		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// ���g�̃|�C���^
		static FirstPersonModuleMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_rotateDegSpeedPerSec{ 100.0f };
		float m_moveSpeedPerSec{ 100.0f };
		bool m_alwaysMoveForward{ false };
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_