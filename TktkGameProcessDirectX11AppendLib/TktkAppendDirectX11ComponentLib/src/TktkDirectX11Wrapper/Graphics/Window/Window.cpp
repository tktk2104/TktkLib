#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Window/WindowManager.h"

namespace tktk
{
	HWND Window::getHWND()
	{
		return WindowManager::getHWND();
	}

	const Vector2 & Window::getWindowSize()
	{
		return WindowManager::getWindowSize();
	}
}