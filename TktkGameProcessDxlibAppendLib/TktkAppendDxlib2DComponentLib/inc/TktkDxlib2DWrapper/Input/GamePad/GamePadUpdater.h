#ifndef GAME_PAD_UPDATER_H_
#define GAME_PAD_UPDATER_H_

#include <vector>
#include <unordered_map>
#include <TktkMath/Vector2.h>
#include "../../DxlibStructWrapper/XInputStateData.h"
#include "../InputType.h"
#include "GamePadNumber.h"
#include "GamePadButtonType.h"

namespace tktk
{
	class GamePadUpdater
	{
	public:

		GamePadUpdater() = default;

	public:

		void awake();

		void update();

	public:

		void setGamePadCount(int gamePadCount);

		bool getState(GamePadNumber padNumber, int inputType, int gamePadButtonType);

		Vector2 getLeftStick(GamePadNumber padNumber, bool getPreviosState = false);

		Vector2 getRightStick(GamePadNumber padNumber, bool getPreviosState = false);

		float getLeftTrigger(GamePadNumber padNumber, bool getPreviosState = false);

		float getRightTrigger(GamePadNumber padNumber, bool getPreviosState = false);

	private:

		bool checkBitFlag(XInputStateData inputState, int gamePadButtonType);

	private:

		int m_gamePadCount;
		std::vector<XInputStateData> m_curState;
		std::vector<XInputStateData> m_preState;
		std::unordered_map<int, int> m_xInputBitFlagMap;
	};
}

#endif // !GAME_PAD_UPDATER_H_
