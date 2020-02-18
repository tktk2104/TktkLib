#include "TktkDxlib2DWrapper/Input/Mouse/Mouse.h"

#include "TktkDxlib2DWrapper/Input/Mouse/MouseManager.h"

namespace tktk
{
	Vector2 Mouse::getCursorPoint()
	{
		return MouseManager::getCursorPoint();
	}

	void Mouse::setCursorPoint(const Vector2 & point)
	{
		MouseManager::setCursorPoint(point);
	}

	void Mouse::showCursor()
	{
		MouseManager::showCursor();
	}

	void Mouse::hideCursor()
	{
		MouseManager::hideCursor();
	}

	bool Mouse::getState(int inputType, int mouseButtonType)
	{
		return MouseManager::getState(inputType, mouseButtonType);
	}

	int Mouse::getVerticalMouseWheel()
	{
		return MouseManager::getVerticalMouseWheel();
	}

	float Mouse::getVerticalMouseWheelF()
	{
		return MouseManager::getVerticalMouseWheelF();
	}

	int Mouse::getHorizontalMouseWheel()
	{
		return MouseManager::getHorizontalMouseWheel();
	}

	float Mouse::getHorizontalMouseWheelF()
	{
		return MouseManager::getHorizontalMouseWheelF();
	}
}