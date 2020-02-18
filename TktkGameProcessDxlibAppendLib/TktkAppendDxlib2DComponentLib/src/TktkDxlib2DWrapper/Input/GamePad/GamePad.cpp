#include "TktkDxlib2DWrapper/Input/GamePad/GamePad.h"

#include "TktkDxlib2DWrapper/Input/GamePad/GamePadManager.h"

namespace tktk
{
	void GamePad::setGamePadCount(int gamePadCount)
	{
		GamePadManager::setGamePadCount(gamePadCount);
	}

	bool GamePad::getState(GamePadNumber padNumber, int inputType, int gamePadButtonType)
	{
		return GamePadManager::getState(padNumber, inputType, gamePadButtonType);
	}

	Vector2 GamePad::getLeftStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return GamePadManager::getLeftStick(padNumber, getPreviosState);
	}

	Vector2 GamePad::getRightStick(GamePadNumber padNumber, bool getPreviosState)
	{
		return GamePadManager::getRightStick(padNumber, getPreviosState);
	}

	float GamePad::getLeftTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return GamePadManager::getLeftTrigger(padNumber, getPreviosState);
	}

	float GamePad::getRightTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		return GamePadManager::getRightTrigger(padNumber, getPreviosState);
	}
}