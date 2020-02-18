#include "TktkDxlib2DWrapper/Input/GamePad/GamePadManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	std::weak_ptr<GamePadUpdater> GamePadManager::m_gamePadUpdater;

	void GamePadManager::setUp()
	{
		auto gamePadUpdater = std::make_shared<GamePadUpdater>();
		ComponentFrameworkProcessor::addClass(gamePadUpdater);
		m_gamePadUpdater = gamePadUpdater;
	}

	void GamePadManager::setGamePadCount(int gamePadCount)
	{
		m_gamePadUpdater.lock()->setGamePadCount(gamePadCount);
	}

	bool GamePadManager::getState(GamePadNumber padNumber, int inputType, int gamePadButtonType)
	{
		return m_gamePadUpdater.lock()->getState(padNumber, inputType, gamePadButtonType);
	}

	Vector2 GamePadManager::getLeftStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater.lock()->getLeftStick(padNumber, getPreviosState);
	}

	Vector2 GamePadManager::getRightStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater.lock()->getRightStick(padNumber, getPreviosState);
	}

	float GamePadManager::getLeftTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater.lock()->getLeftTrigger(padNumber, getPreviosState);
	}

	float GamePadManager::getRightTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater.lock()->getRightTrigger(padNumber, getPreviosState);
	}
}