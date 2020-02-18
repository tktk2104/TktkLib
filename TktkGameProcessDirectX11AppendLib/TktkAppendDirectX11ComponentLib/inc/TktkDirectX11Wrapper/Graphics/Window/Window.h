#ifndef WINDOW_H_
#define WINDOW_H_

#include <TktkMath/Vector2.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// �uWindowManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Window
	{
	public:

		// �E�B���h�E�n���h�����擾����
		static HWND getHWND();

		// �E�B���h�E�T�C�Y���擾����
		static const Vector2& getWindowSize();
	};
}
#endif // !WINDOW_H_