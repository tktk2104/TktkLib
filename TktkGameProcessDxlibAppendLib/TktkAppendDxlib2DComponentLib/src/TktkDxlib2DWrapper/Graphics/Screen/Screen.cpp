#include "TktkDxlib2DWrapper/Graphics/Screen/Screen.h"

#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenManager.h"

namespace tktk
{
	const Vector2 & Screen::getDisplaySize()
	{
		return ScreenManager::getDisplaySize();
	}

	const Vector2 & Screen::getGameScreenSize()
	{
		return ScreenManager::getGameScreenSize();
	}

	const Vector2 & Screen::getLetterBoxSize()
	{
		return ScreenManager::getLetterBoxSize();
	}

	void Screen::backgroundColor(const Color & color)
	{
		return ScreenManager::backgroundColor(color);
	}
}