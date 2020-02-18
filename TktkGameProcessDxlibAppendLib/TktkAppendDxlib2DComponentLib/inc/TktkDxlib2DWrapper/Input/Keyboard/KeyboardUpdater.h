#ifndef KEYBOARD_UPDATER_H_
#define KEYBOARD_UPDATER_H_

#include "../InputType.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class KeyboardUpdater
	{
	public:

		KeyboardUpdater() = default;

	public:

		void update();

	public:

		// ・引数はInputType（ビットフラグ）と
		//   KeyboardKeyTypeの列挙型（非ビットフラグ）
		bool getState(int inputType, KeyboardKeyType keyboardKeyType);

	private:

		char m_curKeycode[256];

		char m_preKeycode[256];
	};
}
#endif // !KEYBOARD_UPDATER_H_