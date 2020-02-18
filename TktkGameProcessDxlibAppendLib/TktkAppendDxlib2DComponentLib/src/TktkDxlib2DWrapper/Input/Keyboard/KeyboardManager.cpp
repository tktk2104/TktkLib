#include "TktkDxlib2DWrapper/Input/Keyboard/KeyboardManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<KeyboardUpdater> KeyboardManager::m_keyboardUpdater;

	void KeyboardManager::setUp()
	{
		auto keyboardUpdater = std::make_shared<KeyboardUpdater>();
		ComponentFrameworkProcessor::addClass(keyboardUpdater);
		m_keyboardUpdater = keyboardUpdater;
	}

	bool KeyboardManager::getState(int inputType, KeyboardKeyType keyboardKeyType)
	{
		return m_keyboardUpdater.lock()->getState(inputType, keyboardKeyType);
	}
}