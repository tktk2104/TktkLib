#include "TktkDirectX11Wrapper/Input/Keyboard/Keyboard.h"

#include "TktkDirectX11Wrapper/Input/Keyboard/KeyboardManager.h"

namespace tktk
{
	bool Keyboard::isPush(KeybordKeyType keyType)
	{
		return KeyboardManager::isPush(keyType);
	}

	bool Keyboard::isTrigger(KeybordKeyType keyType)
	{
		return KeyboardManager::isTrigger(keyType);
	}
}