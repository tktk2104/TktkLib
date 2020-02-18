#include "TktkDxlib2DWrapper/Graphics/Screen/ScreenManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<ScreenUpdater> ScreenManager::m_screenUpdater;

	void ScreenManager::setUp(
		const Vector2& gameScreenSize,
		bool fullScreen
	)
	{
		auto screenUpdater = std::make_shared<ScreenUpdater>(gameScreenSize, fullScreen);
		ComponentFrameworkProcessor::addClass(screenUpdater);
		m_screenUpdater = screenUpdater;
	}

	const Vector2 & ScreenManager::getDisplaySize()
	{
		return m_screenUpdater.lock()->getDisplaySize();
	}

	const Vector2 & ScreenManager::getGameScreenSize()
	{
		return m_screenUpdater.lock()->getGameScreenSize();
	}

	const Vector2 & ScreenManager::getLetterBoxSize()
	{
		return m_screenUpdater.lock()->getLetterBoxSize();
	}

	void ScreenManager::backgroundColor(const Color & color)
	{
		m_screenUpdater.lock()->backgroundColor(color);
	}
}