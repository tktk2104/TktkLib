#ifndef KEYBOARD_MANAGER_H_
#define KEYBOARD_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "KeyboardUpdater.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class KeyboardManager
	{
	public:

		static void setUp();

		// ・引数はInputType（ビットフラグ）と
		//   KeyboardKeyTypeの列挙型（非ビットフラグ）
		static bool getState(int inputType, KeyboardKeyType keyboardKeyType);

	private:

		static CfpPtr<KeyboardUpdater> m_keyboardUpdater;
	};
}

#endif // !KEYBOARD_MANAGER_H_
