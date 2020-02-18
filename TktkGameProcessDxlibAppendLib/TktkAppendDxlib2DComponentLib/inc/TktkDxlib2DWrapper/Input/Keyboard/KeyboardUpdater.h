#ifndef KEYBOARD_UPDATER_H_
#define KEYBOARD_UPDATER_H_

#include "../InputType.h"
#include "KeyboardKeyType.h"

namespace tktk
{
	class KeyboardUpdater
	{
	public:

		KeyboardUpdater() = default;

	public:

		void update();

	public:

		// �E������InputType�i�r�b�g�t���O�j��
		//   KeyboardKeyType�̗񋓌^�i��r�b�g�t���O�j
		bool getState(int inputType, KeyboardKeyType keyboardKeyType);

	private:

		char m_curKeycode[256];

		char m_preKeycode[256];
	};
}
#endif // !KEYBOARD_UPDATER_H_