#ifndef KEY_BOARD_MANAGER_H_
#define KEY_BOARD_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "KeyboardUpdater.h"
#include "KeybordKeyType.h"
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// �uKeyboardUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class KeyboardManager
	{
	public:

		// �uKeyboardUpdater�v�𐶐�
		static void setUp(HINSTANCE hInstance);

	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);

	private:

		static CfpPtr<KeyboardUpdater> m_updaterPtr;
	};
}
#endif // !KEY_BOARD_MANAGER_H_