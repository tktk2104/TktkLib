#include "TktkDxlib2DWrapper/Input/Mouse/MouseManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<MouseUpdater> MouseManager::m_mouseUpdater;

	void MouseManager::setUp()
	{
		m_mouseUpdater = ComponentFrameworkProcessor::addClass(true, new MouseUpdater());
	}

	Vector2 MouseManager::getCursorPoint()
	{
		return m_mouseUpdater->getCursorPoint();
	}

	void MouseManager::setCursorPoint(const Vector2 & point)
	{
		m_mouseUpdater->setCursorPoint(point);
	}

	void MouseManager::showCursor()
	{
		m_mouseUpdater->showCursor();
	}

	void MouseManager::hideCursor()
	{
		m_mouseUpdater->hideCursor();
	}

	bool MouseManager::getState(int inputType, int mouseButtonType)
	{
		return m_mouseUpdater->getState(inputType, mouseButtonType);
	}

	int MouseManager::getVerticalMouseWheel()
	{
		return m_mouseUpdater->getVerticalMouseWheel();
	}

	float MouseManager::getVerticalMouseWheelF()
	{
		return m_mouseUpdater->getVerticalMouseWheelF();
	}

	int MouseManager::getHorizontalMouseWheel()
	{
		return m_mouseUpdater->getHorizontalMouseWheel();
	}

	float MouseManager::getHorizontalMouseWheelF()
	{
		return m_mouseUpdater->getHorizontalMouseWheelF();
	}
}