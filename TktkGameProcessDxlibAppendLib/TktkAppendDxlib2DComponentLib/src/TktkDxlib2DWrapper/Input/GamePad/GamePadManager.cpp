#include "TktkDxlib2DWrapper/Input/GamePad/GamePadManager.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<GamePadUpdater> GamePadManager::m_gamePadUpdater;

	void GamePadManager::setUp()
	{
		m_gamePadUpdater = ComponentFrameworkProcessor::addClass(true, new GamePadUpdater());
	}

	void GamePadManager::setGamePadCount(int gamePadCount)
	{
		m_gamePadUpdater->setGamePadCount(gamePadCount);
	}

	bool GamePadManager::getState(GamePadNumber padNumber, int inputType, int gamePadButtonType)
	{
		return m_gamePadUpdater->getState(padNumber, inputType, gamePadButtonType);
	}

	Vector2 GamePadManager::getLeftStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater->getLeftStick(padNumber, getPreviosState);
	}

	Vector2 GamePadManager::getRightStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater->getRightStick(padNumber, getPreviosState);
	}

	float GamePadManager::getLeftTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater->getLeftTrigger(padNumber, getPreviosState);
	}

	float GamePadManager::getRightTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return m_gamePadUpdater->getRightTrigger(padNumber, getPreviosState);
	}
}