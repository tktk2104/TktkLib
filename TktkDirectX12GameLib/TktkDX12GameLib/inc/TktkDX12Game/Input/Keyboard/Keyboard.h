#ifndef KEY_BOARD_H_
#define KEY_BOARD_H_

#include "KeybordKeyType.h"

namespace tktk
{
	// �uKeyboardManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Keyboard
	{
	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);
	};
}
#endif // !KEY_BOARD_H_