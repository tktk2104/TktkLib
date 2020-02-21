#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<ScreenUpdater> ScreenManager::m_screenUpdater;

	void ScreenManager::setUp(const Vector2& gameScreenSize, bool fullScreen)
	{
		m_screenUpdater = ComponentFrameworkProcessor::addClass(true, new ScreenUpdater(gameScreenSize, fullScreen));
	}

	const Vector2 & ScreenManager::getDisplaySize()
	{
		return m_screenUpdater->getDisplaySize();
	}

	const Vector2 & ScreenManager::getGameScreenSize()
	{
		return m_screenUpdater->getGameScreenSize();
	}

	const Vector2 & ScreenManager::getLetterBoxSize()
	{
		return m_screenUpdater->getLetterBoxSize();
	}

	void ScreenManager::backgroundColor(const Color & color)
	{
		m_screenUpdater->backgroundColor(color);
	}
}