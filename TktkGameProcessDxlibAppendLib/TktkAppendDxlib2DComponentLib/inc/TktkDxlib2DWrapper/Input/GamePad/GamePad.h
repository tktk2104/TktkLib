#ifndef GAME_PAD_H_
#define GAME_PAD_H_

#include <TktkMath/Vector2.h>
#include "GamePadNumber.h"
#include "GamePadButtonType.h"

namespace tktk
{
	class GamePad
	{
	public:

		// 何個のコントローラーを使用するか？（初期値は１個）
		static void setGamePadCount(int gamePadCount);

		// ・引数はGamePadNumberの列挙型（非ビットフラグ）と
		//   InputTypeとGamePadButtonTypeの列挙型（ビットフラグ）
		static bool getState(GamePadNumber padNumber, int inputType, int gamePadButtonType);

		static Vector2 getLeftStick(GamePadNumber padNumber, bool getPreviosState = false);

		static Vector2 getRightStick(GamePadNumber padNumber, bool getPreviosState = false);

		static float getLeftTrigger(GamePadNumber padNumber, bool getPreviosState = false);

		static float getRightTrigger(GamePadNumber padNumber, bool getPreviosState = false);

	};
}
#endif // !GAME_PAD_H_