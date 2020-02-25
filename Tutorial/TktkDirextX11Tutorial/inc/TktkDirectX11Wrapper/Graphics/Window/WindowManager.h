#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "WindowUpdater.h"

namespace tktk
{
	// �uWindowUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class WindowManager
	{
	public:

		// �uWindowUpdater�v�𐶐�
		static void setUp(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string& windowName,
			const Vector2& windowSize
		);

	public:

		// �E�B���h�E�n���h�����擾����
		static HWND getHWND();

		// �E�B���h�E�T�C�Y���擾����
		static const Vector2& getWindowSize();

	private:

		static CfpPtr<WindowUpdater> m_updaterPtr;
	};
}
#endif // !WINDOW_MANAGER_H_