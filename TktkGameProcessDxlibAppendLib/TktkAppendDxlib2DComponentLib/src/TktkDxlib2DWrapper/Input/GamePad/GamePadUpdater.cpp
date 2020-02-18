#include "TktkDxlib2DWrapper/Input/GamePad/GamePadUpdater.h"

#include <algorithm>
#include <DxLib.h>

namespace tktk
{
	void GamePadUpdater::awake()
	{
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_UP_BUTTON,				XINPUT_BUTTON_DPAD_UP));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_DOWN_BUTTON,				XINPUT_BUTTON_DPAD_DOWN));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_LEFT_BUTTON,				XINPUT_BUTTON_DPAD_LEFT));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_RIGHT_BUTTON,				XINPUT_BUTTON_DPAD_RIGHT));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_START_BUTTON,				XINPUT_BUTTON_START));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_BACK_BUTTON,				XINPUT_BUTTON_BACK));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_LEFT_THUMB_BUTTON,		XINPUT_BUTTON_LEFT_THUMB));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_RIGHT_THUMB_BUTTON,		XINPUT_BUTTON_RIGHT_THUMB));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_LEFT_SHOULDER_BUTTON,		XINPUT_BUTTON_LEFT_SHOULDER));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_RIGHT_SHOULDER_BUTTON,	XINPUT_BUTTON_RIGHT_SHOULDER));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_A_BUTTON,					XINPUT_BUTTON_A));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_B_BUTTON,					XINPUT_BUTTON_B));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_X_BUTTON,					XINPUT_BUTTON_X));
		m_xInputBitFlagMap.insert(std::make_pair(GAME_PAD_Y_BUTTON,					XINPUT_BUTTON_Y));
		
		setGamePadCount(1);
	}

	void GamePadUpdater::update()
	{
		m_preState = m_curState;

		for (int i = 1; i <= m_gamePadCount; i++)
		{
			DxLib::XINPUT_STATE rawXInputState;

			GetJoypadXInputState(i, &rawXInputState);

			XInputStateData xInputStateData;

			int itrCount = 0;
			std::for_each(
				std::begin(xInputStateData.buttons),
				std::end(xInputStateData.buttons),
				[&itrCount, &rawXInputState](auto & node) { node = rawXInputState.Buttons[itrCount++]; }
			);

			xInputStateData.leftTrigger = rawXInputState.LeftTrigger;
			xInputStateData.rightTrigger = rawXInputState.RightTrigger;
			xInputStateData.thumbLX = rawXInputState.ThumbLX;
			xInputStateData.thumbLY = rawXInputState.ThumbLY;
			xInputStateData.thumbRX = rawXInputState.ThumbRX;
			xInputStateData.thumbRY = rawXInputState.ThumbRY;

			m_curState.at(i - 1) = xInputStateData;
		}
	}

	void GamePadUpdater::setGamePadCount(int gamePadCount)
	{
		m_gamePadCount = gamePadCount;

		m_curState.clear();
		m_preState.clear();

		m_curState = std::vector<XInputStateData>(gamePadCount, XInputStateData());
		m_preState = std::vector<XInputStateData>(gamePadCount, XInputStateData());
	}

	bool GamePadUpdater::getState(GamePadNumber padNumber, int inputType, int gamePadButtonType)
	{
		if ((inputType & INPUT_BEGIN) != 0)
		{
			if (checkBitFlag(m_curState.at(padNumber - 1), gamePadButtonType)
				&& !checkBitFlag(m_preState.at(padNumber - 1), gamePadButtonType)) return true;
		}

		if ((inputType & INPUT_PUSHING) != 0)
		{
			if (checkBitFlag(m_curState.at(padNumber - 1), gamePadButtonType)) return true;
		}

		if ((inputType & INPUT_ENDED) != 0)
		{
			if (!checkBitFlag(m_curState.at(padNumber - 1), gamePadButtonType)
				&& checkBitFlag(m_preState.at(padNumber - 1), gamePadButtonType)) return true;
		}
		return false;
	}

	Vector2 GamePadUpdater::getLeftStick(GamePadNumber padNumber, bool getPreviosState)
	{
		int x, y;

		XInputStateData& useData = getPreviosState ? m_preState.at(padNumber - 1) : m_curState.at(padNumber - 1);

		x = useData.thumbLX;
		y = useData.thumbLY;

		if (x >= 0) x++;
		if (y >= 0) y++;

		float ansx = static_cast<float>(x) / 32768;
		float ansy = static_cast<float>(y) / 32768;

		return Vector2{ ansx, ansy };
	}

	Vector2 GamePadUpdater::getRightStick(GamePadNumber padNumber, bool getPreviosState)
	{
		int x, y;

		XInputStateData& useData = getPreviosState ? m_preState.at(padNumber - 1) : m_curState.at(padNumber - 1);

		x = useData.thumbRX;
		y = useData.thumbRY;

		if (x >= 0) x++;
		if (y >= 0) y++;

		float ansx = static_cast<float>(x) / 32768;
		float ansy = static_cast<float>(y) / 32768;

		return Vector2{ ansx, ansy };
	}

	float GamePadUpdater::getLeftTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		XInputStateData& useData = getPreviosState ? m_preState.at(padNumber - 1) : m_curState.at(padNumber - 1);

		return useData.leftTrigger;
	}

	float GamePadUpdater::getRightTrigger(GamePadNumber padNumber, bool getPreviosState)
	{
		XInputStateData& useData = getPreviosState ? m_preState.at(padNumber - 1) : m_curState.at(padNumber - 1);

		return useData.rightTrigger;
	}

	bool GamePadUpdater::checkBitFlag(XInputStateData inputState, int gamePadButtonType)
	{
		bool result = false;

		std::for_each(
			std::begin(m_xInputBitFlagMap),
			std::end(m_xInputBitFlagMap),
			[&result, inputState, gamePadButtonType](const auto & node) { result = (node.first & gamePadButtonType) && (inputState.buttons[node.second] == 1); }
		);
		return result;
	}
}