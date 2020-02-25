#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "FirstPersonModule.h"

namespace tktk
{
	// FirstPersonModule�̃C���X�^���X���쐬����\����
	struct FirstPersonModuleMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<FirstPersonModule> create();

		// �}�E�X�J�[�\�����P�s�N�Z���ړ��������̉�]�p�x��ݒ肷��i�x���@�j
		FirstPersonModuleMaker& rotationDegPerPixelOnMouseMove(float value);

		// ���b�ǂꂾ���̑��x�ňړ����邩��ݒ肷��
		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		// ��ɑO���Ɉړ����邩��ݒ肷��
		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		// �X�y�[�X�A�V�t�g�L�[�ŏ㉺�Ɉړ����邩��ݒ肷��
		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// ���g�̃|�C���^
		static FirstPersonModuleMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_rotationDegPerPixelOnMouseMove;
		float m_moveSpeedPerSec;
		bool m_alwaysMoveForward{ false };
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_