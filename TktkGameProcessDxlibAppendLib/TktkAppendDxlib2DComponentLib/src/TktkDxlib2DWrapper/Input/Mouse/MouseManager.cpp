#include "TktkDxlib2DWrapper/Input/Mouse/MouseManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<MouseUpdater> MouseManager::m_mouseUpdater;

	void MouseManager::setUp()
	{
		auto mouseUpdater = std::make_shared<MouseUpdater>();
		ComponentFrameworkProcessor::addClass(mouseUpdater);
		m_mouseUpdater = mouseUpdater;
	}

	Vector2 MouseManager::getCursorPoint()
	{
		return m_mouseUpdater.lock()->getCursorPoint();
	}

	void MouseManager::setCursorPoint(const Vector2 & point)
	{
		m_mouseUpdater.lock()->setCursorPoint(point);
	}

	void MouseManager::showCursor()
	{
		m_mouseUpdater.lock()->showCursor();
	}

	void MouseManager::hideCursor()
	{
		m_mouseUpdater.lock()->hideCursor();
	}

	bool MouseManager::getState(int inputType, int mouseButtonType)
	{
		return m_mouseUpdater.lock()->getState(inputType, mouseButtonType);
	}

	int MouseManager::getVerticalMouseWheel()
	{
		return m_mouseUpdater.lock()->getVerticalMouseWheel();
	}

	float MouseManager::getVerticalMouseWheelF()
	{
		return m_mouseUpdater.lock()->getVerticalMouseWheelF();
	}

	int MouseManager::getHorizontalMouseWheel()
	{
		return m_mouseUpdater.lock()->getHorizontalMouseWheel();
	}

	float MouseManager::getHorizontalMouseWheelF()
	{
		return m_mouseUpdater.lock()->getHorizontalMouseWheelF();
	}
}