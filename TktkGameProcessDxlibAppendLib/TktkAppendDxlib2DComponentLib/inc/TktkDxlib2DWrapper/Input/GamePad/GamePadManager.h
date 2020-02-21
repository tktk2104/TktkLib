#ifndef GAME_PAD_MANAGER_H_
#define GAME_PAD_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkMath/Vector2.h>
#include "GamePadUpdater.h"
#include "GamePadNumber.h"

namespace tktk
{
	class GamePadManager
	{
	public:

		static void setUp();

		// ���̃R���g���[���[���g�p���邩�H�i�����l�͂P�j
		static void setGamePadCount(int gamePadCount);

		// �E������GamePadNumber�̗񋓌^�i��r�b�g�t���O�j��
		//   InputType��GamePadButtonType�̗񋓌^�i�r�b�g�t���O�j
		static bool getState(GamePadNumber padNumber, int inputType, int gamePadButtonType);

		static Vector2 getLeftStick(GamePadNumber padNumber, bool getPreviosState = false);

		static Vector2 getRightStick(GamePadNumber padNumber, bool getPreviosState = false);

		static float getLeftTrigger(GamePadNumber padNumber, bool getPreviosState = false);

		static float getRightTrigger(GamePadNumber padNumber, bool getPreviosState = false);

	private:

		static CfpPtr<GamePadUpdater> m_gamePadUpdater;
	};
}

#endif // !GAME_PAD_MANAGER_H_
