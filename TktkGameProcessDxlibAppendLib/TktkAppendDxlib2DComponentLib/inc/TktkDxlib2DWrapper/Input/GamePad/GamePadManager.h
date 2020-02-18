#ifndef GAME_PAD_MANAGER_H_
#define GAME_PAD_MANAGER_H_

#include <memory>
#include <TktkMath/Vector2.h>
#include "GamePadUpdater.h"
#include "GamePadNumber.h"

namespace tktk
{
	class GamePadManager
	{
	public:

		static void setUp();

		// 何個のコントローラーを使用するか？（初期値は１個）
		static void setGamePadCount(int gamePadCount);

		// ・引数はGamePadNumberの列挙型（非ビットフラグ）と
		//   InputTypeとGamePadButtonTypeの列挙型（ビットフラグ）
		static bool getState(GamePadNumber padNumber, int inputType, int gamePadButtonType);

		static Vector2 getLeftStick(GamePadNumber padNumber, bool getPreviosState = false);

		static Vector2 getRightStick(GamePadNumber padNumber, bool getPreviosState = false);

		static float getLeftTrigger(GamePadNumber padNumber, bool getPreviosState = false);

		static float getRightTrigger(GamePadNumber padNumber, bool getPreviosState = false);

	private:

		static std::weak_ptr<GamePadUpdater> m_gamePadUpdater;
	};
}

#endif // !GAME_PAD_MANAGER_H_
