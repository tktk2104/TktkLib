#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../InputType.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class Keyboard
	{
	public:

		// �E������InputType�i�r�b�g�t���O�j��
		//   KeyboardKeyType�̗񋓌^�i��r�b�g�t���O�j
		static bool getState(int inputType, KeyboardKeyType keyboardKeyType);
	};
}

#endif // !KEYBOARD_H_