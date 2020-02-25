#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "FirstPersonModule.h"

namespace tktk
{
	class FirstPersonModuleMaker
	{
	public:

		// インスタンス作成開始
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<FirstPersonModule> create();

		FirstPersonModuleMaker& rotateDegSpeedPerSec(float value);

		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static FirstPersonModuleMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_rotateDegSpeedPerSec{ 100.0f };
		float m_moveSpeedPerSec{ 100.0f };
		bool m_alwaysMoveForward{ false };
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_