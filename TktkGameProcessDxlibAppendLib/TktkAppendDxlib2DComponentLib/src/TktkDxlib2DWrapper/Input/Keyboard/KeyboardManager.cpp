#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<KeyboardUpdater> KeyboardManager::m_keyboardUpdater;

	void KeyboardManager::setUp()
	{
		m_keyboardUpdater = ComponentFrameworkProcessor::addClass(true, new KeyboardUpdater());
	}

	bool KeyboardManager::getState(int inputType, KeyboardKeyType keyboardKeyType)
	{
		return m_keyboardUpdater->getState(inputType, keyboardKeyType);
	}
}