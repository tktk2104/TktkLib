#include "TktkDirectX11Wrapper/Input/Mouse/Mouse.h"

#include "TktkDirectX11Wrapper/Input/Mouse/MouseManager.h"

namespace tktk
{
	bool Mouse::isPush(MouseButtonType button)
	{
		return MouseManager::isPush(button);
	}

	bool Mouse::isTrigger(MouseButtonType button)
	{
		return MouseManager::isTrigger(button);
	}

	Vector2 Mouse::mousePos()
	{
		return MouseManager::mousePos();
	}
}