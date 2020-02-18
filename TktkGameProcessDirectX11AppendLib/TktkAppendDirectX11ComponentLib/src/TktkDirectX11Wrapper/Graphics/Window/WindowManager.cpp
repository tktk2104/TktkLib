#include "TktkDirectX11Wrapper/Graphics/Window/WindowManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<WindowUpdater> WindowManager::m_updaterPtr;

	void WindowManager::setUp(
		HINSTANCE hInstance,
		int nCmdShow,
		const std::string& windowName,
		const Vector2& windowSize
	)
	{
		m_updaterPtr = ComponentFrameworkProcessor::addClass(true, new WindowUpdater(
			hInstance,
			nCmdShow,
			windowName,
			windowSize
		));
	}

	HWND WindowManager::getHWND()
	{
		return m_updaterPtr->getHWND();
	}

	const Vector2 & WindowManager::getWindowSize()
	{
		return m_updaterPtr->getWindowSize();
	}
}