#include "TktkDirectX11Wrapper/Input/Keyboard/KeyboardManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<KeyboardUpdater> KeyboardManager::m_updaterPtr;

	void KeyboardManager::setUp(HINSTANCE hInstance)
	{
		m_updaterPtr = ComponentFrameworkProcessor::createClass<KeyboardUpdater>(true, hInstance);
	}

	bool KeyboardManager::isPush(KeybordKeyType keyType)
	{
		return m_updaterPtr->isPush(keyType);
	}

	bool KeyboardManager::isTrigger(KeybordKeyType keyType)
	{
		return m_updaterPtr->isTrigger(keyType);
	}
}