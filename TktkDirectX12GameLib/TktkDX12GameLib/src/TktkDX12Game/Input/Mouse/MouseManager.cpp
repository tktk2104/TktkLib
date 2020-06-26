#include "TktkDirectX11Wrapper/Input/Mouse/MouseManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<MouseUpdater> MouseManager::m_updaterPtr;

	void MouseManager::setUp()
	{
		m_updaterPtr = ComponentFrameworkProcessor::createClass<MouseUpdater>(true);
	}

	bool MouseManager::isPush(MouseButtonType button)
	{
		return m_updaterPtr->isPush(button);
	}

	bool MouseManager::isTrigger(MouseButtonType button)
	{
		return m_updaterPtr->isTrigger(button);
	}

	Vector2 MouseManager::mousePos()
	{
		return m_updaterPtr->mousePos();
	}
}