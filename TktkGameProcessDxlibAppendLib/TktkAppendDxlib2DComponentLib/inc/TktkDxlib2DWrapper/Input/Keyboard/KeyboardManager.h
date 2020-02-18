#ifndef KEYBOARD_MANAGER_H_
#define KEYBOARD_MANAGER_H_

#include <memory>
#include "KeyboardUpdater.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class KeyboardManager
	{
	public:

		static void setUp();

		// �E������InputType�i�r�b�g�t���O�j��
		//   KeyboardKeyType�̗񋓌^�i��r�b�g�t���O�j
		static bool getState(int inputType, KeyboardKeyType keyboardKeyType);

	private:

		static std::weak_ptr<KeyboardUpdater> m_keyboardUpdater;
	};
}

#endif // !KEYBOARD_MANAGER_H_
