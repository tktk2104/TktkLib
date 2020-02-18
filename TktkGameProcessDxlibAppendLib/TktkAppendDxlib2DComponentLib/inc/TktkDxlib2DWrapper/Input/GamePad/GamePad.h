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

		// ���̃R���g���[���[���g�p���邩�H�i�����l�͂P�j
		static void setGamePadCount(int gamePadCount);

		// �E������GamePadNumber�̗񋓌^�i��r�b�g�t���O�j��
		//   InputType��GamePadButtonType�̗񋓌^�i�r�b�g�t���O�j
		static bool getState(GamePadNumber padNumber, int inputType, int gamePadButtonType);

		static Vector2 getLeftStick(GamePadNumber padNumber, bool getPreviosState = false);

		static Vector2 getRightStick(GamePadNumber padNumber, bool getPreviosState = false);

		static float getLeftTrigger(GamePadNumber padNumber, bool getPreviosState = false);

		static float getRightTrigger(GamePadNumber padNumber, bool getPreviosState = false);

	};
}
#endif // !GAME_PAD_H_