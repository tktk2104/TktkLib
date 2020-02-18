#ifndef KEYBOARD_MANAGER_H_
#define KEYBOARD_MANAGER_H_

#include <memory>
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

		static std::weak_ptr<KeyboardUpdater> m_keyboardUpdater;
	};
}

#endif // !KEYBOARD_MANAGER_H_
