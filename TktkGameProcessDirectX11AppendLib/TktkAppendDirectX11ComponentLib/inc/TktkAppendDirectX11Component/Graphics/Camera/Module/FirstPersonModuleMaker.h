#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "FirstPersonModule.h"

namespace tktk
{
	class FirstPersonModuleMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<FirstPersonModule> create();

		FirstPersonModuleMaker& rotateDegSpeedPerSec(float value);

		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

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