#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../InputType.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class Keyboard
	{
	public:

		// ・引数はInputType（ビットフラグ）と
		//   KeyboardKeyTypeの列挙型（非ビットフラグ）
		static bool getState(int inputType, KeyboardKeyType keyboardKeyType);
	};
}

#endif // !KEYBOARD_H_