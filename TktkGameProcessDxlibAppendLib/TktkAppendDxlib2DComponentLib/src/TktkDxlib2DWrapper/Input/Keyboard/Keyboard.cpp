#include "TktkDxlib2DWrapper/Input/Keyboard/Keyboard.h"

#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardManager.h"

namespace tktk
{
	bool Keyboard::getState(int inputType, KeyboardKeyType keyboardKeyType)
	{
		return KeyboardManager::getState(inputType, keyboardKeyType);
	}
}